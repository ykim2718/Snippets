"""
y, 2021.2.16
apscheduler - BackgroundScheduler - cron.py
https://apscheduler.readthedocs.io/en/latest/userguide.html
https://github.com/agronholm/apscheduler/tree/master/examples/?at=master
https://lemontia.tistory.com/508
"""

from datetime import datetime
import time
import os
import functools

from apscheduler.schedulers.background import BackgroundScheduler


def tick(_id):
    print('\t' * int(_id) + f"Tick#{_id}! The time is: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")


if __name__ == '__main__':

    scheduler = BackgroundScheduler()
    add_cron_job = functools.partial(scheduler.add_job, func=tick, trigger='cron')
    add_cron_job(id='job#1', second='*/10', args=(1,))
    add_cron_job(id='job#2', minute='35-40, 45-50', second='15, 45', args=(2,))
    scheduler.start()
    print('Press Ctrl+{0} to exit'.format('Break' if os.name == 'nt' else 'C'))

    try:
        # This is here to simulate application activity (which keeps the main thread alive).
        while True:
            time.sleep(5)
    except (KeyboardInterrupt, SystemExit):
        # Not strictly necessary if daemonic mode is enabled but should be done if possible
        scheduler.shutdown()
