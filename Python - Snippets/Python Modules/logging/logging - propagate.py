"""
y, logging - propagate.py, 2017.9.5
"""

import logging
import sys

logging.basicConfig(format='%(asctime)s, %(levelname)s, %(filename)s, %(lineno)d, %(funcName)s(), %(message)s',
                    level=logging.INFO, stream=sys.stdout)
log = logging.getLogger('mother')

log.info('mother logger ..')
child = logging.getLogger('mother.child')
child.propagate = False
child.info('child logger ..')
child.propagate = True
child.info('child logger .. !!')
