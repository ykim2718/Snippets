"""
y, 2022.10.30 - 31
apscheduler - time range.py
"""

from apscheduler.schedulers.blocking import BlockingScheduler
import datetime as dt
import pytz
import time


def my_function(*args):
    print(time.ctime())


tz = pytz.timezone('Asia/Seoul')
bs = BlockingScheduler(timezone=tz)

next_run_time = dt.datetime.now(tz=tz)
# bs.add_job(my_function, 'cron', hour='0-23', minute='*')  # every minute, same as minute='0-59'
bs.add_job(my_function, 'cron', hour='0-23')  # every hour, same as minute=None

bs.print_jobs()
for job in bs.get_jobs():
    print(f"{job.id=}: {job.trigger}")
bs.start()

