"""
y, 2023.1.1
apscheduler - reschedule_job.py
https://apscheduler.readthedocs.io/en/3.x/modules/job.html?highlight=reschedule#apscheduler.job.Job.reschedule
"""

from apscheduler.schedulers.blocking import BlockingScheduler
from apscheduler.triggers.cron import CronTrigger
from apscheduler.triggers.cron.fields import DayOfWeekField


def my_func():
    print('my_func')


bs = BlockingScheduler()

trigger = CronTrigger(day_of_week='mon-fri', hour=14, minute=34, second=50)
bs.add_job(my_func, trigger, misfire_grace_time=120, jitter=10, id='y')
bs.print_jobs()
# my_func (trigger: cron[day_of_week='mon-fri', hour='14', minute='34', second='50'], pending)
job = bs.get_job('y')
bs.reschedule_job(job_id="y", trigger='cron', minute=30)
bs.print_jobs()
# my_func (trigger: cron[minute='30'], next run at: 2023-01-01 14:30:00 KST)

dow_index = CronTrigger.FIELD_NAMES.index('day_of_week')
trigger.fields[dow_index] = DayOfWeekField('day_of_week', 'mon')
bs.add_job(my_func, trigger, misfire_grace_time=120, jitter=10, id='y')
bs.print_jobs()
# my_func (trigger: cron[day_of_week='mon', hour='14', minute='34', second='50'], pending)
