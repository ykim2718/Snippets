"""
y, 2022.5.9
apscheduler - basic.py
https://apscheduler.readthedocs.io/en/3.x/userguide.html
https://github.com/agronholm/apscheduler/blob/3.x/examples/schedulers/blocking.py
"""

from apscheduler.schedulers.background import BackgroundScheduler
from apscheduler.schedulers.blocking import BlockingScheduler
import pytz
import time
from datetime import datetime

from apscheduler.schedulers.blocking import BlockingScheduler


def tick():
    print('Tick! The time is: %s' % datetime.now())


if __name__ == '__main__':
    scheduler = BlockingScheduler(timezone=pytz.timezone('Asia/Seoul'))
    scheduler.add_job(tick, 'interval', seconds=3)
    print('Press Ctrl+{0} to exit'.format('Break' if os.name == 'nt' else 'C'))

    try:
        scheduler.start()
    except (KeyboardInterrupt, SystemExit):
        pass
