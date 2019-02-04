import re


CONFIG_LINE_PATTERN = r"(\w+|\*)\.(\w+|\*)\.([0-9]?[0-9]|\*)\.(\w+|\*)\.\w+\s*=\s*\w+"


def should_skip(line):
    return not line.strip() or line.strip().startswith('#')


def verify(line):
    # env.host.app_id.section.key=value
    # env.app_id.instance_id.section.key=value
    if not re.match(CONFIG_LINE_PATTERN, line):
        raise ValueError("invalid config line:[{}]".format(line))
    return True
