"""
y, apscheduler - eval 1st.py, 2017.7.30

http://apscheduler.readthedocs.io/en/latest/modules/triggers/cron.html  ★★★
"""

from apscheduler.schedulers.blocking import BlockingScheduler


def my_function(*args):
    print("Hello apscheduler ..", args)


bs = BlockingScheduler()

# bs.add_job(job_function, 'cron', month='6-8,11-12', day='3rd fri', hour='0-3')
bs.add_job(my_function, 'cron', day_of_week='mon-fri', hour=14, minute=34, second=50, args=['args here'])

bs.print_jobs()
# for job in bs.get_jobs():
#     print(job, type(job), job.trigger)

bs.start()

