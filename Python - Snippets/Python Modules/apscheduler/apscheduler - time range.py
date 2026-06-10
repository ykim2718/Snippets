"""
y, 2022.10.30 - 31, 11.11
apscheduler - time range.py
"""

from apscheduler.schedulers.blocking import BlockingScheduler
import datetime as dt
import pytz
import time


def my_function(*args, _count=[0]):
    _count[0] += 1
    print(f"{_count[0]=}", time.ctime())
    time.sleep(60*2)


tz = pytz.timezone('Asia/Seoul')
bs = BlockingScheduler(timezone=tz)

next_run_time = dt.datetime.now(tz=tz)
bs.add_job(my_function, 'cron', hour='0-23', minute='*')  # every minute, same as minute='0-59'
"""
_count[0]=1 Fri Nov 11 22:07:00 2022
Execution of job "my_function (trigger: cron[hour='0-23', minute='*'], next run at: 2022-11-11 22:08:00 KST)" skipped: maximum number of running instances reached (1)
Execution of job "my_function (trigger: cron[hour='0-23', minute='*'], next run at: 2022-11-11 22:09:00 KST)" skipped: maximum number of running instances reached (1)
_count[0]=2 Fri Nov 11 22:10:00 2022
Execution of job "my_function (trigger: cron[hour='0-23', minute='*'], next run at: 2022-11-11 22:11:00 KST)" skipped: maximum number of running instances reached (1)
_count[0]=3 Fri Nov 11 22:12:00 2022
Execution of job "my_function (trigger: cron[hour='0-23', minute='*'], next run at: 2022-11-11 22:13:00 KST)" skipped: maximum number of running instances reached (1)
Execution of job "my_function (trigger: cron[hour='0-23', minute='*'], next run at: 2022-11-11 22:14:00 KST)" skipped: maximum number of running instances reached (1)
_count[0]=4 Fri Nov 11 22:15:00 2022
"""
# bs.add_job(my_function, 'cron', hour='0-23')  # every hour, same as minute=None

bs.print_jobs()
for job in bs.get_jobs():
    print(f"{job.id=}: {job.trigger}")
bs.start()

