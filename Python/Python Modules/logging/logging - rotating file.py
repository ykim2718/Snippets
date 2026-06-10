"""
y, ~2020.3.7
http://stackoverflow.com/questions/13733552/logger-configuration-to-log-to-file-and-print-to-stdout
"""

import logging
import sys
import path

log = logging.getLogger('')
log.setLevel(logging.DEBUG)
format = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")

ch = logging.StreamHandler(sys.stdout)
ch.setFormatter(format)
log.addHandler(ch)

LOGFILE = pathlib.Path(__file__).with_suffix('.log')
fh = logging.handlers.RotatingFileHandler(LOGFILE, maxBytes=(1048576 * 5), backupCount=7)
fh.setFormatter(format)
log.addHandler(fh)

log.error("User error message")
