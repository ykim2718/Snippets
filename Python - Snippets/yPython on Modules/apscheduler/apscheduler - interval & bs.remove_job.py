"""
y, apscheduler - interval.py, 2024.4.4

https://apscheduler.readthedocs.io/en/3.x/modules/triggers/interval.html#module-apscheduler.triggers.interval
https://apscheduler.readthedocs.io/en/3.x/userguide.html#removing-jobs
https://apscheduler.readthedocs.io/en/3.x/userguide.html#pausing-and-resuming-jobs
https://apscheduler.readthedocs.io/en/latest/modules/schedulers/base.html#apscheduler.schedulers.base.BaseScheduler
    . state (int) – current running state of the scheduler
        (one of the following constants from apscheduler.schedulers.base: STATE_STOPPED, STATE_RUNNING, STATE_PAUSED)
https://stackoverflow.com/questions/33036321/python-apscheduler-not-stopping-a-job-even-after-using-remove-job
"""

from apscheduler.schedulers.blocking import BlockingScheduler
import pandas as pd


def my_function(*args, _count=[0], **kwargs):
    bs = kwargs['bs']
    job_id = kwargs['job_id']
    job = bs.get_job(job_id)
    now = pd.Timestamp.now()
    print(f"Hello apscheduler .. {job.pending=}, {args=}, {len(kwargs)=} at {now}")
    start_time = kwargs['start_time'].split(':')
    stop_time = kwargs['stop_time'].split(':')
    start_time = now.normalize().replace(hour=int(start_time[0]), minute=int(start_time[1]), second=int(start_time[2]))
    stop_time = now.normalize().replace(hour=int(stop_time[0]), minute=int(stop_time[1]), second=int(stop_time[2]))
    _count[0] += 1
    if start_time <= now <= stop_time:
        print(f"\t[{_count[0]}] {start_time=}, {stop_time=}")
    elif stop_time < now:
        print(f"\t[{_count[0]}] bs.remove_job(job_id)")
        # bs.remove_job(job_id)  # permanent remove; TODO 2024.4.5, how to resume job ???
        bs.pause_job(job_id)  # TODO 2024.4.5, how to resume job ??


bs = BlockingScheduler()

job_id = 'my_job'
start_date = None
stop_date = None  # '09:00'
now = pd.Timestamp.now(tz='Asia/Seoul')
start_time = now.strftime("%H:%M:%S")
stop_time = (now + pd.Timedelta(seconds=10)).strftime("%H:%M:%S")
# bs.add_job(my_function, 'interval', minutes=1, start_date=start_date, end_date=stop_date, args=['args here'])
job = bs.add_job(
    my_function, 'interval', seconds=2, start_date=start_date, end_date=stop_date,
    args=['args here'], id=job_id, kwargs=dict(bs=bs, job_id=job_id, start_time=start_time, stop_time=stop_time))
print(f"{bs.state=}")
print(f"{bs.get_job(job_id)=}")
bs.print_jobs()

bs.start()

