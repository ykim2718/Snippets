"""
yLog-User.py
y (copyRight) 2016.4.30
"""

from y.core.yLog import ySetLogger, GetLogger


def testLogInfo():
    GetLogger().info("hello")


def testFunctionArgument(arg_int):
    """
    y (copyRight) 2016.5.1
    """

    if isinstance(arg_int, int) is False:
        log = "argument {} must be {}, not {}"
        log = log.format(0, type(int()), not arg_int)
        GetLogger().critical(log)
        raise AssertionError(log)

    GetLogger().info("argument %s passed" % arg_int)


def testLogCriticalWithTryExcept():
    try:
        1 / 0
    except Exception as ex:
        log = "%s, %s" % (type(ex).__name__, ex)
        GetLogger().critical(log)
        raise RuntimeError(log)


if __name__ == '__main__':
    file = __file__[:-3] + '.log'
    ySetLogger(log_file=file, log_to_where='Both')
    yLogger = GetLogger()
    yLogger.info("User starts here")
    testLogInfo()
    testFunctionArgument(1.)
    testLogCriticalWithTryExcept()
