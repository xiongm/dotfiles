#!/usr/bin/env python3

import subprocess
from optparse import OptionParser, OptionGroup
import os
import signal
import unittest
import uuid
import sys
import time
import json
from datetime import datetime
from contextlib import contextmanager


import logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


CONF_FILE = "go.conf"
AUTO_GENERATED_CONFIG = [
 {
     'name': 'test',
     'command': 'sleep 1'
 }
]
COLOR_DICT = {
        'red': "\033[1;31m",
        'blue': "\033[1;34m",
        'cyan': "\033[1;36m",
        'green': "\033[0;32m",
        'reset': "\033[0;0m",
        'bold': "\033[;1m"
}

def parse_args():
    usage = "%prog [init|start|stop|restart|status|cleanup]"
    ops_parser = OptionParser(usage)
    ops_parser.add_option("-t", action="store_true", dest="unit_test", help="run unit test")

    start_ops_group = OptionGroup(ops_parser, "Start options", "")
    start_ops_group.add_option("-p", "--prefix", type="string", action="store", dest="config_file_prefix", help="user defined config directory")
    ops_parser.add_option_group(start_ops_group)

    options, args = ops_parser.parse_args()
    return options, args, ops_parser


def color_print(content, color='reset', end="\n"):
    global COLOR_DICT
    print("{}{}{}".format(COLOR_DICT[color], content, COLOR_DICT['reset']), end=end)


class Process(object):

    def __init__(self, name, cmd, init_cmd=None, pid_log=None, log_dir=None, verbose=False):
        self.name = name.strip(' ').replace(' ', '_')
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
        curr_dir = os.getcwd()
        self.pid_log = (pid_log if pid_log else curr_dir) + '/{}.pid'.format(self.name)
        self.log_dir = log_dir if log_dir else curr_dir
        self.std_log = self.log_dir + '/' + '{}.log.{}'.format(self.name, datetime.now().strftime("%Y%m%d"))
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
            with open(self.std_log, "w") as f:
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
        if (os.path.exists(self.pid_log)):
            os.remove(self.pid_log)
        if self.verbose:
            self.show_status('stop', redundant=not currently_running)

    def cleanup(self):
        currently_running = self.running()
        if not currently_running:
            if os.path.exists(self.std_log):
                os.remove(self.std_log)
            if (os.path.exists(self.pid_log)):
                os.remove(self.pid_log)
        else:
            color_print("{} is running [pid {}]. cleanup not applicable".format(self.name, self.pid), color='red')
            return
        if self.verbose:
            self.show_status('cleanup')

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
        if os.path.isfile(self.pid_log):
            with open(self.pid_log, "r") as pid_file:
                pid = pid_file.read()
        return int(pid) if pid else None

    @pid.setter
    def pid(self, pid):
        with open(self.pid_log, "w") as pid_file:
            pid_file.write(str(pid) + '\n')


def load_apps(configs):
    apps = []
    for cfg in configs:
        name = cfg['name']
        command = cfg['command']
        pid_log = cfg.get('pid_log', config_path)
        log_dir = cfg.get('log_dir', config_path)
        apps.append(Process(name, command, pid_log, log_dir, verbose=True))
    return apps

class TestProcess(unittest.TestCase):
    @staticmethod
    @contextmanager
    def create_test_dir():
        import shutil
        test_dir = '/tmp/{}'.format(uuid.uuid1())
        os.mkdir(test_dir)
        yield test_dir
        shutil.rmtree(test_dir)


    def test_start_stop(self):
        with TestProcess.create_test_dir() as test_dir:
            ps = Process("test", "sleep 30", pid_log=test_dir)
            ps.start()
            self.assertTrue(ps.running())
            ps.stop()
            self.assertFalse(ps.running())

    def test_no_stop_but_finished_process(self):
        with TestProcess.create_test_dir() as test_dir:
            ps = Process("test", "sleep 1", pid_log=test_dir)
            ps.start()
            self.assertTrue(ps.running())
            os.wait()
            self.assertFalse(ps.running())


if __name__ == "__main__":
    options, args, ops_parser = parse_args()

    if options.unit_test:
        unittest.main(argv=sys.argv[1:])
        sys.exit(0)

    config_path = os.path.abspath(options.config_file_prefix) if options.config_file_prefix else os.getcwd()

    if not len(args):
        ops_parser.print_help()
        exit(-1)

    config_file = os.path.join(config_path, CONF_FILE)
    if not os.path.exists(config_file):
        with open(config_file, 'w') as f:
            f.write(json.dumps(AUTO_GENERATED_CONFIG, indent=4))
            f.write('\n')
        print("go: no such config - {}".format(config_file))
        print("generated for you, please try again")
        exit(-1)

    apps_config = json.load(open(config_file, 'r'))
    assert isinstance(apps_config, list) and len(apps_config)


    apps = load_apps(apps_config)

    cmds = []
    cmds.append(args[0])
    while(len(cmds)):
        cmd = cmds.pop(0)
        if cmd == 'init':
            for app in apps:
                app.init()
        elif cmd == 'start':
            for app in apps[:-1]:
                app.start()
                time.sleep(0.3)
            else:
                apps[-1].start()
        elif cmd == 'status':
            for app in apps:
                app.show_status(cmd)
        elif cmd == 'stop':
            for app in apps:
                app.stop()
        elif cmd == 'cleanup':
            for app in apps:
                app.cleanup()
        elif cmd == 'restart':
            cmds.append('stop')
            cmds.append('start')
        else:
            ops_parser.print_help()
