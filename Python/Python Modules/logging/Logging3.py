"""
http://stackoverflow.com/questions/13733552/logger-configuration-to-log-to-file-and-print-to-stdout
"""

import logging, os


def SwitchLogToScreenOrFile(logToWhere):
    """
    Y, 2016.4.13
    :param logToWhere: 0 None, 1 Screen, 2 File, 3 Both
    :return: None
    """

    logFormatter = logging.Formatter(
        "%(asctime)s [%(threadName)-12.12s] [%(levelname)-5.5s]  %(message)s")
    rootLogger = logging.getLogger()
    rootLogger.setLevel(logging.DEBUG)

    log_file = __file__ + ".log"
    try:
        os.remove(log_file)
    except:
        pass

    if logToWhere == 0:
        rootLogger.disabled = True
    else:
        if (logToWhere == 1 \
                    or logToWhere == 3):
            consoleHandler = logging.StreamHandler()
            consoleHandler.setFormatter(logFormatter)
            rootLogger.addHandler(consoleHandler)
        if (logToWhere == 2 \
                    or logToWhere == 3):
            fileHandler = logging.FileHandler(log_file)
            fileHandler.setFormatter(logFormatter)
            rootLogger.addHandler(fileHandler)


if __name__ == '__main__':
    logToWhere = 2
    SwitchLogToScreenOrFile(logToWhere)
    logging.info(repr(logToWhere))
    logging.error("User error message")
