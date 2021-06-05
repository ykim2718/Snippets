"""
y, 2020.3.6
logging - subclass.py
"""

import logging


class YLogStdout:

    def debug(self, *args, **kwargs):
        print('\33[33m', *args, '\33[0m', **kwargs)  # yellow

    def warning(self, *args, **kwargs):
        print('\33[31m', *args, '\33[0m', **kwargs)  # red

    def info(self, *args, **kwargs):
        print('\33[34m', *args, '\33[0m', **kwargs)  # blue


class YLogStdout2:

    def __init__(self, name=None):
        ch = logging.StreamHandler()
        formatter = logging.Formatter('%(asctime)s %(levelname)8s %(name)s | %(message)s')
        ch.setFormatter(formatter)
        logger = logging.getLogger(name or __class__.__name__)
        logger.addHandler(ch)
        logger.setLevel(logging.DEBUG)
        self.logger = logger

    def __getattr__(self, name):
        return getattr(self.logger, name)


if __name__ == '__main__':

    logger = YLogStdout()
    logger.debug('No sweat, no sweet.')
    logger.info('No pain, no gain.')
    logger.warning('Easy come, easy go.')
    logger.critical('Early bird catches the worm.')

    logger = YLogStdout2()
    logger.debug('debug')
    logger.info('info')
    logger.warning('warning')
