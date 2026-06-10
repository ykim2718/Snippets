"""
y, 2022.9.13
apscheduler - next_run_time.py
"""

from apscheduler.schedulers.blocking import BlockingScheduler
import datetime as dt
import pytz


def my_function(*args):
    print("Hello apscheduler ..", args)


tz = pytz.timezone('Asia/Seoul')
bs = BlockingScheduler(timezone=tz)

next_run_time = dt.datetime.now(tz=tz)
# next_run_time = None
bs.add_job(my_function, 'cron', day_of_week='mon-fri', hour=23, next_run_time=next_run_time)

bs.print_jobs()
for job in bs.get_jobs():
    print(f"{job.id=}: {job.trigger}")
bs.start()

