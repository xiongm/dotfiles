#!/usr/bin/python

""" trcsql - bootstrap sql generation tool

* Generate sql queries for various trc db operations
* it queries current db to provide suggested values
* it DOES NOT, WILL NOT perform db update operation on production tables
* due to discrepancy between canada and us trc db, it currently only supports canada

To use it

1. ./trcsql.py
2. choose action and follow instructions
3. peer review generated trcsql.sql and modify manually if needed
4. psql trc -f trcsql.sql
5. done


as of 2016/12, it is available only in cntrc1

Preresuiqsite
===================================================================
currently assumes the following script/binaries in the same directory
* allocate_ports.sh
* allocate_ports

Notes for supported actions

Add session
===================================================================
* generate SQLs for new_listen_ports and new_exchange_ports only
* automatically allocate new ports based on existing ports


"""
from __future__ import print_function

from psycopg2 import connect
from optparse import OptionParser
import subprocess
import time
import signal
import sys
import unittest

trcsql_version = "1.0"

def welcome():
  subprocess.call('clear', shell=True)
  print ('\n' * 3)
  print ("Trcsql " + trcsql_version + " " + time.strftime("%c"))
  print ("trcsql is a bootstrap tool for sql sript generations")
  print ("(Enter/Choose new value, or press ENTER for default, Ctr-c to exit anytime)")

def goodbye():
  print ("Thank you for using trcsql. Goodbye")

class simpleDBWrapper:
  def __init__(self, db):
    self.db = db

  # execute sql and return a sequence of rows
  # with each row being a column->value hash table
  def query(self, query):
    c = self.db.cursor()
    c.execute(query)
    # description is a vector of vector
    # first item of each vector is field name
    fields = [i[0] for i in c.description]
    rows = c.fetchall()
    # return a sequence of hash table
    return [dict(zip(fields, row)) for row in rows]

# trc dbwrapper to convert db results to python data structures (sequence or dict)
# used to provide options for user input
class trcDBWrapper(simpleDBWrapper):
  def get_market_handler_hosts(self):
    records = self.query("select market_handler_uid, market_handler_name from market_handler")
    res = {}
    for record in records:
      res[record['market_handler_uid']] = record['market_handler_name']
    return res

  def get_clients(self):
    records = self.query("select client_accounts_uid, client_accounts_name from client_accounts")
    res = {}
    for record in records:
      res[record['client_accounts_uid']] = record['client_accounts_name']
    return res

  def get_protocols(self):
    records = self.query("select distinct protocol from exchange_ports where protocol != ''")
    return [record['protocol'] for record in records]

  def get_exchange_codes(self, protocol):
    records = self.query("select distinct exchange_code from exchange_ports where protocol = '%s'" % (protocol))
    return [record['exchange_code'] if record['exchange_code'] else '' for record in records]

  def listen_ports_field_by_mh(self, field, market_handler_uid):
    records = self.query("select distinct %s from listen_ports where market_handler_uid = %s" % (field, market_handler_uid))
    return [str(record[field]) for record in records] if records else [''] 

  def exchange_ports_field_by_protocol_and_mh(self, field, protocol, market_handler_uid):
    records = self.query("select distinct %s from exchange_ports where protocol = '%s' and market_handler_uid = %s" % (field, protocol, market_handler_uid))
    return [str(record[field]) for record in records] if records else ['']


# abstract generator class
class trcSQLGenerator:
  def __init__(self, dbw):
    self.dbw = dbw

  def generate(self, params):
    raise NotImplementedError("Implement me please")


# derived generator class for session addition
class trcAddSessionSQLGenerator(trcSQLGenerator):

  def generate(self, params):
    num = params['num_of_sessions']
    res = []
    ret, ports = self._assign_ports(params['market_handler_host'], num)
    if (len(ports) < int(num)):
      print ("Notice: not enough ports available. requested:", num, " actual:", len(ports))

    if (len(ports) == 0):
      return None

    res.append("BEGIN;")
    # new_listen_ports insert sql generation
    for port in ports:
      sql = ("INSERT INTO new_listen_ports "
             "(market_handler_uid, listen_ports_type, listen_ports_port, client_accounts_uid, s1, s2, s3) "
             "VALUES ('%s', 'CLIENT','%s', '%s', 'xgbe1', '%s', '%s');" %
             (params['market_handler_uid'], port, params['client_accounts_uid'], params['listen_s2'], params['listen_s3'])
            )
      res.append(sql)
    # new_exchange_ports insert sql generation
    for port in ports:
      sql = ("INSERT INTO new_exchange_ports "
             "(market_handler_uid, protocol, ip, port, s1, s2, s3, s4, s5, exchange_code) "
             "VALUES ('%s', '%s', '%s', '%s', 'xgbe1', '%s', '%s', '%s', '%s', '%s');" %
             (params['market_handler_uid'], params['exchange_protocol'], params['exchange_ip'], params['exchange_port'], params['exchange_s2'], params['exchange_s3'], params['exchange_s4'], port, params['exchange_code'])
            )
      res.append(sql)
    res.append("COMMIT;")
    return res

  # use shell commands to invoke ports allocation scripts
  # ideally these should all be written in python
  def _assign_ports(self, mh_name, num):
    res = []
    pipe = subprocess.Popen("./allocate_ports.sh %s %s | awk '{if (NR > 1) print}'" % (mh_name, num), shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    ret = pipe.wait()
    for line in pipe.stdout.readlines():
      # exclude the '\n'
      res.append(line[0:-1])
    return ret, res


# inputGuide provides input prompt for users
class inputGuide:
  S_VERTICAL = 0
  S_HORIZONTAL = 1
  """ prompt user with multiple options to select from

   Arguments:
   :param message: customized message for prompt
   :param options: supports sequence (keys are values) or dict (keys and values)
   :param style: - S_VERTICAL
                      key1 key1-item1
                      key2 key2-item2
                      key3 key3-item3
                   S_HORIZONTAL
                      key1/key2/key3
   :param display_indent: indentation for options menu, only applicable for S_VERTICAL
   :param return_key_value: return both key and value if True, default is False
  """
  def select(self, message, options, style=S_VERTICAL, display_indent=2, return_key_value=False, allow_override=False):
    if (not options):
      return ''
    if isinstance(options, dict):
      # convert keys to strings, python 2.6
      # does not support dict comprehensions
      # so these codes are not very pythonic
      normed_options = {}
      for key, value in options.iteritems():
        normed_options[str(key)] = value
      options = normed_options
      # dict are not sorted, sometimes it will distort the order of menus
      keys = sorted(options.keys())
    else:
      keys = options

    if (style == inputGuide.S_VERTICAL):
      for key in keys:
        print (' ' * display_indent + ((key + ' - ' + options[key]) if isinstance(options, dict) else (('* ') + key)))

    default_response = keys[0]
    while 1:
      if (style == inputGuide.S_VERTICAL):
        self._prompt(message, default_response)
      elif (style == inputGuide.S_HORIZONTAL):
        # DEFAULT/non_default
        self._prompt(message, keys[0].upper() + '/'.join(keys)[len(keys[0]):])
      response = raw_input("") or default_response
      if (response not in keys):
        if (allow_override):
          if (self.confirm("Your input does not match any of the choices, are you sure?") == 'y'):
            break
        else:
          print ("Invalid input:" + response)
      else:
        break
    if (return_key_value):
      return (response, options[response]) if isinstance(options, dict) else (response, response)
    else:
      return response

  def confirm(self, message):
    return self.select(message, ['y', 'n'], style=inputGuide.S_HORIZONTAL)

  """ prmopt user for input with a default value"""
  def read(self, message, default=''):
    self._prompt(message, default)
    response = raw_input("") or default
    return response

  def _prompt(self, message, options):
    print ("%s [%s]: " % (message, options), end="")


def getAddSessionParams(dbw):
  params = {}
  guide = inputGuide()
  mh_hosts_options = dbw.get_market_handler_hosts()
  clients_options = dbw.get_clients()
  protocol_options = dbw.get_protocols()
  while 1:
    while 1:
      try:
        tmp = guide.read("Enter number of sessions you would like to request", '1')
        params['num_of_sessions'] = int(tmp)
        break
      except ValueError:
        print (tmp, "is not a valid number")
    market_handler_uid, market_handler_host = guide.select("Choose target market handler id", mh_hosts_options, return_key_value=True)
    params['market_handler_uid'] = market_handler_uid
    params['market_handler_host'] = market_handler_host
    params['client_accounts_uid'] = guide.select("Choose client account id", clients_options)
    params['listen_s2'] = guide.select("Enter listen ports s2 (Client-side Vlan)", dbw.listen_ports_field_by_mh('s2', market_handler_uid), allow_override=True)
    params['listen_s3'] = guide.select("Enter listen ports s3 (Client-side target IP)", dbw.listen_ports_field_by_mh('s3', market_handler_uid), allow_override=True)
    params['exchange_protocol'] = guide.select("Enter exchange protocol", protocol_options, allow_override=True)
    exchange_code_options = dbw.get_exchange_codes(params['exchange_protocol'])
    # select if there are options, read if there are none available
    if (exchange_code_options):
      params['exchange_code'] = guide.select("Enter exchange code", exchange_code_options, allow_override=True)
    else:
      params['exchange_code'] = guide.read("Enter exchange code")
    params['exchange_ip'] = guide.select("Enter exchange ip", dbw.exchange_ports_field_by_protocol_and_mh('ip', params['exchange_protocol'], market_handler_uid), allow_override=True)
    params['exchange_port'] = guide.select("Enter exchange port", dbw.exchange_ports_field_by_protocol_and_mh('port', params['exchange_protocol'], market_handler_uid), allow_override=True)
    params['exchange_s2'] = guide.select("Enter exchange ports s2 (Exchange-side Vlan)", dbw.exchange_ports_field_by_protocol_and_mh('s2', params['exchange_protocol'], market_handler_uid), allow_override=True)
    params['exchange_s3'] = guide.select("Enter exchange ports s3 (Exchange-side target IP)", dbw.exchange_ports_field_by_protocol_and_mh('s3', params['exchange_protocol'], market_handler_uid), allow_override=True)
    params['exchange_s4'] = guide.select("Enter exchange ports s4 (Exchange-side gateway IP)", dbw.exchange_ports_field_by_protocol_and_mh('s4', params['exchange_protocol'], market_handler_uid), allow_override=True)

    print ('=' * 80)
    print ('* General')
    print ('  num of sessions [%s]' % params['num_of_sessions'])
    print ('  market_handler_uid [%s]' % params['market_handler_uid'])
    print ('  client_accounts_uid [%s]' % params['client_accounts_uid'])
    print ('')
    print ('* Listen ports')
    print ('  s2 [%s], s3 [%s]' % (params['listen_s2'], params['listen_s3']))
    print ('')
    print ('* Exchange ports')
    print ('  protocol [%s], exchange_code [%s]' % (params['exchange_protocol'], params['exchange_code']))
    print ('  ip [%s], port [%s]' % (params['exchange_ip'], params['exchange_port']))
    print ('  s2 [%s], s3 [%s], s4 [%s]' % (params['exchange_s2'], params['exchange_s3'], params['exchange_s4']))
    print ('=' * 80)

    if (guide.confirm("Is all information correct (n to start over)?") == 'y'):
      break
  return params

# place holder
class TestTrcGen(unittest.TestCase):
  def setUp(self):
    return "not implemented"

  def tearDown(self):
    return "not implemented"

  def test_basic(self):
    assert False, "TODO:finish me"

# do not trigger backtrace if user needs to exit midway
def sigint_handler(signum, frame):
  sys.stdout.write('\n')
  sys.exit(-1)

def parse_args():
  opt_parser = OptionParser(usage="%prog [-t]")
  opt_parser.add_option("-t", "--test", action="store_true", dest="unit_test", default=False, help="run unit test")
  (options, args) = opt_parser.parse_args()
  return options

def main():
  options = parse_args()
  if options.unit_test:
    suite = unittest.TestLoader().loadTestsFromTestCase(TestTrcGen)
    unittest.TextTestRunner().run(suite)
    return 0
  signal.signal(signal.SIGINT, sigint_handler)
  welcome()
  db = connect(database="trc")
  dbw = trcDBWrapper(db)
  res = []
  try:
    guide = inputGuide()
    actions = {'1': 'Add market handler sessions',
               '2': 'Reserved',
               '3': 'Reserved'}
    action = guide.select('For which action would you like to generate queries?', actions, style=inputGuide.S_VERTICAL)
    # currently only support add sessions
    if (action == '1'):
      params = getAddSessionParams(dbw)
      generator = trcAddSessionSQLGenerator(dbw)
      res = generator.generate(params)
  finally:
    db.close()
  if res:
    print ("Generating trcsql.sql ...")
    with open('./trcsql.sql', 'w') as output_file:
      for line in res:
        output_file.write("%s\n" % line)
    print ("Done. use 'psql trc -f trcsql.sql' to execute")
  else:
    print ("No sql generated")
  goodbye()
  return 0


if __name__ == "__main__":
  main()
