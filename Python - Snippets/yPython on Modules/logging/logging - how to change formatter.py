"""
y, 2020.3.20
logging - how to change formatter.py
"""

import logging

logger = logging.getLogger('my_logger')
ch = logging.StreamHandler()
formatter = logging.Formatter('%(name)s %(levelname)6s: %(message)s')
ch.setFormatter(formatter)
logger.addHandler(ch)
logger.setLevel(logging.INFO)
logger.info(f"logger id={id(logger)}, name={logger.name}, format={logger.handlers[0].formatter._fmt}")
logger.info('Hello ...')
for _logger in [logging.getLogger(name) for name in logging.root.manager.loggerDict]:
    for h in _logger.handlers:
        logger.info(f"_logger id={id(_logger)}, name={_logger.name}, format={h.formatter._fmt}")
        h.setFormatter(logging.Formatter('>>> ' + h.formatter._fmt))
logger.info('... world')

