"""
y, 2022.10.30
apscheduler - time range.py
"""

from apscheduler.schedulers.blocking import BlockingScheduler
import datetime as dt
import pytz
import time


def my_function(*args):
    print(ime.ctime())


tz = pytz.timezone('Asia/Seoul')
bs = BlockingScheduler(timezone=tz)

next_run_time = dt.datetime.now(tz=tz)
# next_run_time = None
bs.add_job(my_function, 'cron', hour='0-23', minute='*')  # same as minute='0-59'

bs.print_jobs()
for job in bs.get_jobs():
    print(f"{job.id=}: {job.trigger}")
bs.start()

