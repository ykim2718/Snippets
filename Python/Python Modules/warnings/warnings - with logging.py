"""
y, warnings - with logging.py, 2017.8.18

https://docs.python.org/2/library/logging.html#logging.captureWarnings

"""

import warnings
import logging


log = logging.getLogger()
log.setLevel(logging.DEBUG)
logFormatter = logging.Formatter('%(asctime)s, %(levelname)s, %(filename)s(%(lineno)d), %(funcName)s(), %(message)s')
console_handler = logging.StreamHandler()
console_handler.setFormatter(logFormatter)
log.addHandler(console_handler)
log.info(__file__)

warnings.warn('warning ... 1')

logging.captureWarnings(True)
warnings.warn('warning ... 2')

logging.captureWarnings(False)
warnings.warn('warning ... 3')

