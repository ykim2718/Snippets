"""
y, apscheduler - shutdown.py, 2023.1.31
"""

from apscheduler.schedulers.blocking import BlockingScheduler
import datetime as dt


def my_function(scheduler, *args):
    print(f"Hello apscheduler .. {args=}")
    scheduler.shutdown(wait=False)
    print('.. shutdowned')


now = dt.datetime.now()
print(f"{now=}")
eta = now + dt.timedelta(seconds=15)
print(f"{eta=}")  # Estimated Time of Arrival

bs = BlockingScheduler()
bs.add_job(my_function, 'cron', day_of_week='mon-fri', hour=eta.hour, minute=eta.minute, second=eta.second,
           args=(bs, 'args here'))
bs.print_jobs()
bs.start()

