import pytest
import sys
from cat.oneconfig import OneConfig

from cat.oneconfig.tests.utils import patch_open


@pytest.mark.parametrize(
    'test_file_input, expected_value', [
        ("""
         *.*.*.section.key=v1
         """,
         'v1'),
        ("""
         *.*.*.section.key=v1
         *.*.*.section.key=v2
         """,
         'v2'),
        ("""
         *.*.*.section.key=v1
         *.*.*.section1.key=v2
         """,
         'v1'),
        ("""
         *.*.*.section.key=v1
         *.*.0.section.key=v2
         """,
         'v2'),
        ("""
         *.*.*.section.key=v1
         *.*.00.section.key=v2
         """,
         'v2')
    ]
)
def test_basic_read(test_file_input, expected_value):
    with patch_open(test_file_input) as mock_file:
        c = OneConfig('path/to/file')
        mock_file.assert_called_with('path/to/file', 'r')
        assert c.config['section']['key'] == expected_value


if __name__ == "__main__":
    sys.exit(pytest.main(['--show-capture=stdout', '-vvsx', __file__]))
