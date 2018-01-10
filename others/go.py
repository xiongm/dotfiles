import subprocess
from optparse import OptionParser, OptionGroup
import os
import signal
import unittest
import uuid
import sys
import time
from datetime import datetime


import logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


def parse_args():
    usage = "%prog [init|start|stop|restart|status] [options]"
    ops_parser = OptionParser(usage)
    ops_parser.add_option("-t", action="store_true", dest="unit_test", help="run unit test")

    start_ops_group = OptionGroup(ops_parser, "Start options", "")
    start_ops_group.add_option("-c", "--config", type="string", action="store", dest="config_file", help="user defined config")
    ops_parser.add_option_group(start_ops_group)

    options, args = ops_parser.parse_args()
    return options, args, ops_parser

color_dict = {
        'red': "\033[1;31m",
        'blue': "\033[1;34m",
        'cyan': "\033[1;36m",
        'green': "\033[0;32m",
        'reset': "\033[0;0m",
        'bold': "\033[;1m"
}

def color_print(content, color='reset', end="\n"):
    global color_dict
    print("{}{}{}".format(color_dict[color], content, color_dict['reset']), end=end)


class Process(object):

    def __init__(self, name, cmd, init_cmd=None, pid_dir=None, log_dir=None, verbose=False):
        self.name = name
        try:
            assert os.path.isdir(self.cmd)
            self.cmd = os.path.abspath(cmd)
        except Exception:
            self.cmd = cmd
        try:
            assert os.path.isdir(self.init_cmd)
            self.init_cmd = os.path.abspath(init_cmd)
        except Exception:
            self.init_cmd = init_cmd
        curr_dir = os.path.dirname(os.path.realpath(__file__))
        self.pid_dir = pid_dir if pid_dir else curr_dir + '/{}.pid'.format(self.name)
        self.log_dir = log_dir if log_dir else curr_dir
        self.verbose = verbose

    def init(self):
        if not self.init_cmd:
            return None
        args = self.init_cmd.split(' ')
        ps = subprocess.Popen(args)
        return ps.wait()

    def start(self):
        currently_running = self.running()
        if not currently_running:
            args = self.cmd.split(' ')
            std_log = self.log_dir + '/' + '{}.log.{}'.format(self.name, datetime.now().strftime("%Y%m%d"))
            with open(std_log, "w") as f:
                ps = subprocess.Popen(args, stdout=f, stderr=f)
            self.pid = ps.pid
        if self.verbose:
            self.show_status('start', redundant=currently_running)

    def restart(self):
        self.stop()
        self.start()

    def stop(self):
        currently_running = self.running()
        if currently_running:
            os.kill(self.pid, signal.SIGKILL)
            os.remove(self.pid_dir)
        if self.verbose:
            self.show_status('stop', redundant=not currently_running)

    def running(self):
        pid = self.pid
        if not pid:
            return False
        return os.path.isdir('/proc/{}'.format(pid))

    def show_status(self, action, redundant=False):
        color_print(action, color='red', end="")
        color_print(' {}: '.format(self.name), color='cyan', end="")
        if redundant:
            color_print("Already ", color='reset', end="")
        if self.running():
            color_print("running", color='reset', end="")
            color_print(" [pid {}]".format(self.pid), color='green')
        else:
            color_print("stopped", color='reset')

    @property
    def pid(self):
        pid = None
        if os.path.isfile(self.pid_dir):
            with open(self.pid_dir, "r") as pid_file:
                pid = pid_file.read()
        return int(pid) if pid else None

    @pid.setter
    def pid(self, pid):
        with open(self.pid_dir, "w") as pid_file:
            pid_file.write(str(pid))



class TestProcess(unittest.TestCase):
    def test_start_stop(self):
        ps = Process("test", "sleep 30", pid_dir="/tmp/{}".format(uuid.uuid1()))
        ps.start()
        self.assertTrue(ps.running())
        ps.stop()
        self.assertFalse(ps.running())

    def test_no_stop_but_finished_process(self):
        ps = Process("test", "sleep 1", pid_dir="/tmp/{}".format(uuid.uuid1()))
        ps.start()
        self.assertTrue(ps.running())
        os.wait()
        self.assertFalse(ps.running())


if __name__ == "__main__":
    options, args, ops_parser = parse_args()

    if options.unit_test:
        unittest.main(argv=sys.argv[1:])
        sys.exit(0)

    if not len(args):
        ops_parser.print_help()
        exit(-1)

    cmd = args[0]
    ps = Process("sleep", "sleep 10", verbose=True)
    if cmd == 'init':
        ps.init()
    elif cmd == 'start':
        ps.start()
    elif cmd == 'status':
        ps.show_status(cmd)
    elif cmd == 'stop':
        ps.stop()
    elif cmd == 'restart':
        ps.restart()
    else:
        ops_parser.print_help()
