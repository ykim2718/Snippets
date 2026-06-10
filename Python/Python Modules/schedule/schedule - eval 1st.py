"""
y, Schedule - eval 1st.py, 2017.6.9

https://schedule.readthedocs.io/en/stable/
https://schedule.readthedocs.io/en/stable/api.html

y found at 2017.6.9
    . heavy load delays following scheduling very seriously.
    . it is probably because almost same cores are used for threading.
    . multi-processing is recommended rather than threading.

"""

import threading
import time
import schedule
import datetime as dt
import math


def eval_factorial(val):

    job_name = 'factorial(%g)' % val
    print(job_name, dt.datetime.now(), threading.current_thread())
    math.factorial(val)
    print('%s %s ended' % (job_name, dt.datetime.now()))

def run_thread(func, arg):

    job_thread = threading.Thread(target=lambda: func(arg))
    job_thread.start()

start = dt.datetime.now() + dt.timedelta(minutes=1)
start = "%s:%s" % (start.hour, start.minute)
print('.. scheduled at', start)

schedule.every().day.at(start).do(run_thread, eval_factorial, 1e6)
schedule.every().day.at(start).do(run_thread, eval_factorial, 5e5)
schedule.every().day.at(start).do(run_thread, eval_factorial, 2e5)
schedule.every().day.at(start).do(run_thread, eval_factorial, 1e5)

print('.. waiting')

while True:

    schedule.run_pending()
    time.sleep(1)  # must need otherwise spends core a lot, 2017.6.10

print('.. ended')



