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
    time.sleep(60*5)


tz = pytz.timezone('Asia/Seoul')
bs = BlockingScheduler(timezone=tz)

next_run_time = dt.datetime.now(tz=tz)
bs.add_job(my_function, 'cron', hour='0-23', minute='*')  # every minute, same as minute='0-59'
# Execution of job "my_function (trigger: cron[hour='0-23', minute='*'], next run at: 2022-10-31 16:29:00 KST)" skipped: maximum number of running instances reached (1)
# bs.add_job(my_function, 'cron', hour='0-23')  # every hour, same as minute=None

bs.print_jobs()
for job in bs.get_jobs():
    print(f"{job.id=}: {job.trigger}")
bs.start()

