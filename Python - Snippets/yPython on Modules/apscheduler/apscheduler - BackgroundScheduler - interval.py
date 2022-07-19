"""
y, 2021.2.14 - 15
apscheduler - BackgroundScheduler - interval.py
https://apscheduler.readthedocs.io/en/latest/userguide.html
https://github.com/agronholm/apscheduler/tree/master/examples/?at=master
https://lemontia.tistory.com/508
"""

from datetime import datetime
import time
import os

from apscheduler.schedulers.background import BackgroundScheduler


def tick(_id):
    print('\t' * int(_id) + f"Tick#{_id}! The time is: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")


if __name__ == '__main__':

    scheduler = BackgroundScheduler()
    scheduler.add_job(tick, 'interval', seconds=1, args=(1,))
    scheduler.add_job(tick, 'interval', seconds=1.3, args=(2,))
    scheduler.start()
    print('Press Ctrl+{0} to exit'.format('Break' if os.name == 'nt' else 'C'))

    try:
        # This is here to simulate application activity (which keeps the main thread alive).
        while True:
            time.sleep(5)
    except (KeyboardInterrupt, SystemExit):
        # Not strictly necessary if daemonic mode is enabled but should be done if possible
        scheduler.shutdown()
