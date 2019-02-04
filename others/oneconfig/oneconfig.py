from collections import defaultdict
from cat.oneconfig import line_parser as lp


class OneConfig(object):

    """Docstring for OneConfig. """

    def __init__(self, config_path, env='*', app_id='*', instance_id=0):
        self.config_path = config_path
        self.config = defaultdict(dict)
        self.env = env
        self.app_id = app_id
        self.instance_id = instance_id
        self.load(self.config_path)

    def load(self, config_path):
        with open(config_path, "r") as cfg:
            for l in cfg:
                l = l.strip()
                if not lp.should_skip(l):
                    if lp.verify(l):
                        self.scan(l)

    def scan(self, line):
        k, v = line.split('=')
        env, app_id, instance_id, section, key = k.split('.')
        print(env, app_id, instance_id, section, key)
        if self.match(env, app_id, instance_id):
            self.config[section][key] = v

    def match(self, env, app_id, instance_id):
        return (env == '*' or self.env == env) & \
            (app_id == '*' or self.app_id == app_id) & \
            (instance_id == '*' or self.instance_id == int(instance_id))
