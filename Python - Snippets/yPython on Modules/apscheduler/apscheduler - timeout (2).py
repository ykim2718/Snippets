"""
y, 2022.5.9, 7.20
apscheduler - timeout (2).py
https://apscheduler.readthedocs.io/en/3.x/userguide.html
https://apscheduler.readthedocs.io/en/3.x/py-modindex.html
https://github.com/agronholm/apscheduler/blob/3.x/examples/schedulers/blocking.py
"""

from apscheduler.schedulers.background import BackgroundScheduler
from apscheduler.schedulers.blocking import BlockingScheduler
import pytz
import datetime as dt
import os

from apscheduler.schedulers.blocking import BlockingScheduler


def tick():
    print('Tick! The time is: %s' % dt.datetime.now())


def my_shutdown(my_scheduler):
    print(f"my_shutdown: {dt.datetime.now()=}")
    my_scheduler.shutdown(wait=False)


if __name__ == '__main__':
    scheduler = BlockingScheduler(timezone=pytz.timezone('Asia/Seoul'))
    scheduler.add_job(tick, 'interval', seconds=2)
    if False:
        scheduler.add_job(my_shutdown, 'date', run_date=dt.datetime.now() + dt.timedelta(seconds=5), args=[scheduler])
    else:
        scheduler.add_job(lambda s=scheduler: s.shutdown(wait=False), 'date',
                          run_date=dt.datetime.now() + dt.timedelta(seconds=5), args=[scheduler])
    print('Press Ctrl+{0} to exit'.format('Break' if os.name == 'nt' else 'C'))

    try:
        scheduler.start()
    except (KeyboardInterrupt, SystemExit):
        pass
