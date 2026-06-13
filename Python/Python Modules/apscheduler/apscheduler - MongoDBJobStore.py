"""
y, 2021.2.15
apscheduler - MongoDBJobStore.py
https://apscheduler.readthedocs.io/en/v3.6/modules/jobstores/mongodb.html
https://blog.naver.com/PostView.nhn?blogId=imcjpak1k&logNo=221737678370&parentCategoryNo=&categoryNo=15&viewDate=&isHowPopularPosts=true&from=search
"""

# TODO 2021.2.15, Don't know how to use MongDBJobStore ????

from apscheduler.schedulers.background import BackgroundScheduler
from apscheduler.jobstores.mongodb import MongoDBJobStore
# from apscheduler.jobstores.sqlalchemy import SQLAlchemyJobStore
from apscheduler.executors.pool import ThreadPoolExecutor, ProcessPoolExecutor
from datetime import datetime
import time
import os


def tick(_id):
    print('\t' * int(_id) + f"Tick#{_id}! The time is: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")


if __name__ == '__main__':

    jobstores = {
        'default': MongoDBJobStore(database='apscheduler', collection='jobs', host='10.0.0.10', port=27117),
    }
    executors = {
        'default': ThreadPoolExecutor(20),
        'processpool': ProcessPoolExecutor(5)
    }
    job_defaults = {
        'coalesce': False,
        'max_instances': 3
    }
    scheduler = BackgroundScheduler(
        jobstores=jobstores, executors=executors, job_defaults=job_defaults, timezone='Asia/Seoul')
    scheduler.add_job(tick, 'cron', id='job#1', second='*/5', args=(1,))
    scheduler.add_job(tick, 'cron', id='job#2', second='*/7', args=(2,))
    scheduler.start()
    print('Press Ctrl+{0} to exit'.format('Break' if os.name == 'nt' else 'C'))

    try:
        # This is here to simulate application activity (which keeps the main thread alive).
        while True:
            time.sleep(5)
    except (KeyboardInterrupt, SystemExit):
        # Not strictly necessary if daemonic mode is enabled but should be done if possible
        scheduler.shutdown()
