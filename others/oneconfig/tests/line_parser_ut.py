import pytest
import sys
from cat.oneconfig.line_parser import should_skip, verify


@pytest.mark.parametrize(
    'config_line', [
        ("#*.*.*.section.key=v1"),
        (""),
        ("      "),
        ("     #")
    ]
)
def test_should_skip(config_line):
    assert should_skip(config_line)


@pytest.mark.parametrize(
    'config_line', [
        ("*.*.*.section.key=v1"),
        ("      *.*.*.section.key=v1")
    ]
)
def test_should_not_skip(config_line):
    assert not should_skip(config_line)


@pytest.mark.parametrize(
    'config_line', [
        ("*.*.*.section.key=v1"),
        ("*.*.*.*.key=v1"),
        ("env.*.*.section.key=v1"),
        ("env.app.*.section.key=v1"),
        ("env.app.0.section.key=v1"),
        ("*.app.*.section.key=v1"),
        ("*.app.0.section.key=v1"),
        ("*.*.01.section.key=v1"),
        ("env.*.01.section.key=v1"),
        ("env.app.01.section.key=v1"),
        ("env.app.01.section.key= v1 "),
        ("env.app.01.section.key=v1 # comment")
    ]
)
def test_valid_config_line(config_line):
    assert verify(config_line)


@pytest.mark.parametrize(
    'config_line', [
        ("*.*.*.section.key="),
        ("@.*.*.section.key=v1"),
        ("*.@.*.section.key=v1"),
        ("*.*.@.section.key=v1"),
        ("@.*.*.section.key.*=v1"),
        ("*.*.000.section.key=v1"),
        ("*.*.*.section.key=@"),
        ("*.*.*.*.*=v1")
    ]
)
def test_invalid_config_line(config_line):
    with pytest.raises(ValueError):
        verify(config_line)

if __name__ == "__main__":
    sys.exit(pytest.main(['--show-capture=stdout', '-vvsx', __file__]))
