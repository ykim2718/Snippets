"""
y, 2021.2.15
apscheduler - BlockingScheduler - cron.py,
https://apscheduler.readthedocs.io/en/latest/modules/triggers/cron.html?highlight=add_job
"""

from datetime import datetime
from apscheduler.schedulers.blocking import BlockingScheduler
import functools


def tick(_id):
    print('\t' * int(_id) + f"Tick#{_id}! The time is: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")


if __name__ == '__main__':

    scheduler = BlockingScheduler()
    scheduler.add_job(tick, 'cron', id='job#1', second='*/5', args=(1,))
    add_cron_job = functools.partial(scheduler.add_job, func=tick, trigger='cron')
    add_cron_job(id='job#2', second='*/7', args=(2,))
    print(f"get_jobs={scheduler.get_jobs()}")
    scheduler.print_jobs()
    scheduler.start()
