"""
y, Schedule - using subprocess.py, 2017.6.19

https://pypi.python.org/pypi/schedule
https://schedule.readthedocs.io/en/stable
"""


import time
import schedule
import datetime as dt
import math
import subprocess


def run_python_script(*args, **kwargs):
    """ y, 2017.6.19 """

    _print_start_log = 'print_start_log'
    _print_stop_log = 'print_stop_log'

    if _print_start_log in kwargs:
        if kwargs[_print_start_log] is True:
            print('>> %s at %s' % (args[0], dt.datetime.now()), args, kwargs)

    args = list(map(str, args))
    with subprocess.Popen(['python', args[0], *args[1:]],
                          stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE,
                          bufsize=1,
                          universal_newlines=True) as p:
        for line in p.stdout:
            print(line, end='')
        for line in p.stderr:
            print(line, end='')

    if _print_stop_log in kwargs:
        if kwargs[_print_stop_log] is True:
            print('>> return code = %s from %s at %s' % (p.returncode, p.pid, dt.datetime.now()))


if __name__ == '__main__':

    start = dt.datetime.now() + dt.timedelta(minutes=1)
    start = "%s:%s" % (start.hour, start.minute)
    print('.. scheduled at', start)

    script = 'run - factorial calc.py'

    schedule.every().day.at(start).do(run_python_script, *(script, 1e6, 1))
    schedule.every().day.at(start).do(run_python_script, *(script, 5e5, 1, 2), **dict(print_start_log=True,
                                                                                      print_stop_log=True))
    schedule.every().day.at(start).do(run_python_script, script, 2e5, 3)
    schedule.every().day.at(start).do(run_python_script, script, 1e5, 4)

    print('.. waiting')

    while True:

        schedule.run_pending()
        time.sleep(1)  # must need otherwise spends core a lot, 2017.6.10

    print('.. ended')
