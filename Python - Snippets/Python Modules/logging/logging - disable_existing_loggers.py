"""
y, 2020.3.7
logging - disable_existing_loggers.py
"""

import logging
import logging.config
import platform as pf

logger1 = logging.getLogger('1')
logger2 = logging.getLogger('2')

if pf.python_version() < '3.8':
    logging.basicConfig()
else:
    logging.basicConfig(force=True)
logger3 = logging.getLogger('3')

log_dictionary = {
    'version': 1,
    # 'disable_existing_loggers': False,  # default is True
    'formatters': {
        'typical': {
            'format': '%(asctime)s %(levelname)s %(name)s | %(filename)s, %(lineno)d: %(message)s',
            'datefmt': '%Y-%m-%d %H:%M:%S'
        }
    },
    'handlers': {
        'console': {
            'class': 'logging.StreamHandler',
            'formatter': 'typical',
            'stream': 'ext://sys.stderr',
        }
    },
    'root': {
        'level': 'DEBUG',
        'handlers': ['console'],
    }
}
logging.config.dictConfig(log_dictionary)
logger4 = logging.getLogger('4')

print(f"logger1: {logger1}, disabled={logger1.disabled}")
print(f"logger2: {logger2}, disabled={logger2.disabled}")
print(f"logger3: {logger3}, disabled={logger3.disabled}")
print(f"logger4: {logger4}, disabled={logger4.disabled}")
