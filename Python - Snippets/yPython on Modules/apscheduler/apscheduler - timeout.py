"""
y, 2022.5.9
apscheduler - timeout.py
https://apscheduler.readthedocs.io/en/3.x/userguide.html
https://github.com/agronholm/apscheduler/blob/3.x/examples/schedulers/blocking.py
"""

from apscheduler.schedulers.background import BackgroundScheduler
from apscheduler.schedulers.blocking import BlockingScheduler
import pytz
import datetime as dt
from multiprocessing import Process


def block_schedule():

    def tick():
        print('Tick! The time is: %s' % dt.datetime.now())

    scheduler = BlockingScheduler(timezone=pytz.timezone('Asia/Seoul'))
    scheduler.add_job(tick, 'interval', seconds=2)
    scheduler.start()


if __name__ == '__main__':

    print('started', dt.datetime.now())
    mp = Process(target=block_schedule)
    mp.start()
    mp.join(timeout=10)
    mp.terminate()
    print('ended..', dt.datetime.now())
