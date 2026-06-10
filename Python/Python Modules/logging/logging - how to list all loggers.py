"""
y, 2020.3.7
logging - how to list all loggers.py
"""

import logging

loggers = [logging.getLogger()]  # get the root logger
loggers = loggers + [logging.getLogger(name) for name in logging.root.manager.loggerDict]
print(loggers)
