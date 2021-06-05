"""
y, 2020.3.6
logging - how to track disabled.py
https://stackoverflow.com/questions/28694540/python-default-logger-disabled/28694704#28694704
"""

import logging
import sys


def get_disabled(self):
    return self._disabled


def set_disabled(self, disabled):
    frame = sys._getframe(1)
    if disabled:
        print('{}:{} disabled the {} logger'.format(
            frame.f_code.co_filename, frame.f_lineno, self.name))
    self._disabled = disabled


# logging.Logger._disabled = logging.Logger.disabled
logging.Logger.disabled = property(get_disabled, set_disabled)
logging.getLogger('foo.bar').disabled = True
