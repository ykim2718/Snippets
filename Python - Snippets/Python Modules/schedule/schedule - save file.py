"""
y, Schedule - save file.py, 2018.4.3

https://pypi.python.org/pypi/schedule
https://schedule.readthedocs.io/en/stable/
https://schedule.readthedocs.io/en/stable/api.html

"""

import threading
import time
import schedule
import datetime as dt
import os


def save_file(file_name):

    file_path = os.path.splitext(__file__)[0] + ' - %s.txt' % file_name
    this_thread = threading.current_thread()

    print(file_path, this_thread, dt.datetime.now(), lock.locked())

    lock.acquire(timeout=3600)  # 1 hour blocking
    f = open(file_path, 'w')
    f.write(str(this_thread))
    f.close()
    print('wrote the file ..', this_thread, dt.datetime.now())
    time.sleep(90)  # to make a conflict to another thread, intentionally
    lock.release()


def run_thread(func, arg):

    job_thread = threading.Thread(target=lambda: func(arg))
    job_thread.start()

start = dt.datetime.now() + dt.timedelta(minutes=1)
start1 = "%s:%s" % (start.hour, start.minute)
start = start + dt.timedelta(minutes=1)
start2 = "%s:%s" % (start.hour, start.minute)
print('scheduled jobs at', start1, start2)

lock = threading.Lock()

schedule.every().day.at(start1).do(run_thread, save_file, 'data')
schedule.every().day.at(start2).do(run_thread, save_file, 'data')

print('waiting ..', dt.datetime.now())

while True:

    schedule.run_pending()
    time.sleep(1)  # must need otherwise spends core a lot, 2017.6.10

print('.. ended')


"""
scheduled at 19:37 19:37
.. waiting 2018-04-03 19:36:05.956172
D:/Wolf/Homo academicus/yStudy on code - Python/Python - Y/yPython on Schedule/Schedule - save file - data.txt <Thread(Thread-1, started 12792)> 2018-04-03 19:37:00.999013 False
D:/Wolf/Homo academicus/yStudy on code - Python/Python - Y/yPython on Schedule/Schedule - save file - data.txt <Thread(Thread-2, started 3984)> 2018-04-03 19:37:00.999013 True
wrote the file .. <Thread(Thread-1, started 12792)> 2018-04-03 19:37:01.000013
wrote the file .. <Thread(Thread-2, started 3984)> 2018-04-03 19:38:31.003689
"""
