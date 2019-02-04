from unittest.mock import patch, mock_open
from contextlib import contextmanager


def my_mock_open(*args, **kargs):
    f_open = mock_open(*args, **kargs)
    f_open.return_value.__iter__ = lambda self: iter(self.readline, '')
    return f_open


@contextmanager
def patch_open(test_data):
    with patch('builtins.open', my_mock_open(read_data=test_data)) as mock_file:
        yield mock_file
