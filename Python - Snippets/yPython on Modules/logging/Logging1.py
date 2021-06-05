"""
Python Essential Reference, David M. Beazley, 4ed, 2009, pp. 355-69.
https://docs.python.org/2/howto/logging.html
"""

import logging


def yLoggerSet(to0None1Screen2File3Both=1, loggingLevel=logging.DEBUG):
    """
    Y (copyRight) 2016.4.13
    :param to0None1Screen2File3Both: 0 none, 1 screen, 2 file, 3 both
    :param loggingLevel: NOTSET, DEBUG, INFO, WARNING, ERROR, CRITICAL
    :return: None
    :Bug: 2 is not working, working same as 3
    """

    logger = logging.getLogger('Y')
    logger.disabled = not to0None1Screen2File3Both  # logging.disable(logging.CRITICAL)

    ch = logging.StreamHandler()
    # ch.setLevel(logging.NOTSET)
    formatter = logging.Formatter(
        '%(asctime)s - %(name)s , %(levelname)s, %(filename)s, %(funcName)s, (%(lineno)d) - %(message)s')
    ch.setFormatter(formatter)
    logger.addHandler(ch)

    logger.setLevel(loggingLevel)

    if to0None1Screen2File3Both >= 2:
        logging.basicConfig(filename=__file__ + '.log', filemode='w')
        logger.info("Let's get the ball rolling")

    return logger


if __name__ == "__main__":
    logger = yLoggerSet(1, logging.DEBUG)
    logger.debug('debug message')
    logger.info('infor message')
    logger.warn('warn message')
    logger.error('error message')
    logger.critical('critical message')
