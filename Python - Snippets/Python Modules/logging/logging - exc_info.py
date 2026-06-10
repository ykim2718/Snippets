"""
y, logging - exc_info.py, 2017.9.5, 9.9; 2021.1.22
"""

import logging

# logging.basicConfig(level=logging.INFO)
log = logging.getLogger(__name__)
log.setLevel(logging.DEBUG)

log_formatter = logging.Formatter(
    '%(asctime)s, %(levelname)s, %(filename)s, %(lineno)d, %(funcName)s(), %(processName)s, %(message)s')
console_handler = logging.StreamHandler()
console_handler.setFormatter(log_formatter)
log.addHandler(console_handler)
file_handler = logging.FileHandler(__file__[:-2] + 'log')
file_handler.setFormatter(log_formatter)
log.addHandler(file_handler)
log.info(__file__)

log.info('- ' * 32)
try:
    assert False
except AssertionError as ex:
    log.info("assertion error ....", exc_info=True)
    log.exception(ex)  # 2021.1.22

log.info('- ' * 32)
try:
    raise Exception('user exception')
# except Exception as ex:
except:
    log.info("exception error ....", exc_info=True)


