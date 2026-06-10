"""
y, 2024.12.5
apscheduler - listener.py
"""

from apscheduler.schedulers.background import BlockingScheduler, BackgroundScheduler
from apscheduler.events import EVENT_JOB_EXECUTED
import pytz
import datetime as dt
import pandas as pd


def job1():
    print(f"job1 at {pd.Timestamp.now()}" )


def job2():
    print(f"job2 at {pd.Timestamp.now()}" )


tz = pytz.timezone('Asia/Seoul')
bs = BlockingScheduler(timezone=tz)


def print_next_schedule(event, scheduler=bs):
    jobs = scheduler.get_jobs()
    next_job = min(jobs, key=lambda job: job.next_run_time)
    print(f"\t{event.job_id=}, {next_job.id=}, {next_job.next_run_time=:{'%H:%M:%S'}}")


next_run_time = dt.datetime.now(tz=tz)
bs.add_job(job1, 'interval', seconds=10, next_run_time=next_run_time, id='job1')
bs.add_job(job2, 'interval', seconds=7, next_run_time=next_run_time, id='job2')
bs.add_listener(print_next_schedule, EVENT_JOB_EXECUTED)

bs.start()

"""
job1 at 2024-12-05 13:30:06.374920
job2 at 2024-12-05 13:30:06.374920
	event.job_id='job2', next_job.id='job2', next_job.next_run_time=03:30:06
	event.job_id='job1', next_job.id='job2', next_job.next_run_time=03:30:13
job2 at 2024-12-05 13:30:13.356693
	event.job_id='job2', next_job.id='job1', next_job.next_run_time=03:30:16
job1 at 2024-12-05 13:30:16.365786
	event.job_id='job1', next_job.id='job2', next_job.next_run_time=03:30:20
job2 at 2024-12-05 13:30:20.364069
	event.job_id='job2', next_job.id='job1', next_job.next_run_time=03:30:26
"""

