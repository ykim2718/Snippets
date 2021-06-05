"""
y, 2020.9.23
logging - basic (2).py
"""

import logging
import os

logger = logging.getLogger('my_logger')
ch = logging.StreamHandler()
logging_format = f"pid={os.getpid()}, %(levelname)5s, %(filename)s, %(lineno)d, %(message)s"
formatter = logging.Formatter(logging_format)
ch.setFormatter(formatter)
logger.addHandler(ch)
logger.setLevel(logging.INFO)
logger.info(f"logger id={id(logger)}, name={logger.name}, format={logger.handlers[0].formatter._fmt}")
logger.info('Hello ... my_logger !!!')
