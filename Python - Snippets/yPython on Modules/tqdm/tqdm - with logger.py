"""
y, 2020.9.23
tqdm - with logger.py
https://github.com/tqdm/tqdm
https://tqdm.github.io/docs/tqdm/
    >> ncols: The width of the entire output message
"""

import logging
import os
import types
import tqdm
import time

logger = logging.getLogger('my_logger')
ch = logging.StreamHandler()
logging_format = f"pid={os.getpid()}, %(levelname)5s, %(filename)s, %(lineno)d, %(message)s"
formatter = logging.Formatter(logging_format)
ch.setFormatter(formatter)
logger.addHandler(ch)
logger.setLevel(logging.DEBUG)
logger.info(f"logger id={id(logger)}, name={logger.name}, format={logger.handlers[0].formatter._fmt}")
logger.info('Hello ... my_logger !!!')


def my_write(log, text):
    if text and text.strip():
        log.debug(text.strip())


logger.write = types.MethodType(my_write, logger)

with tqdm.tqdm(total=100, ncols=80, desc='updating', unit='byte', file=logger) as pbar:
    for j in range(10):
        time.sleep(0.1)
        pbar.update(10)
