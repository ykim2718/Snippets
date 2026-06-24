"""
y, 2022.3.30
pyqt5 - qtscheduler.py
https://stackoverflow.com/questions/63893509/pyqt5-thread-issues-with-schedule-and-timer
"""

from datetime import datetime
from apscheduler.schedulers.qt import QtScheduler
from PyQt5 import QtCore


class Scheduler(QtCore.QObject):
    started = QtCore.pyqtSignal(object)
    completed = QtCore.pyqtSignal(object)

    def __init__(self):
        self.id = 'test_job'
        self.sched = QtScheduler()

    def add(self, job_function, *args, **kwargs):
        self.sched.add_job(self.createJob(job_function), 'cron',
                           day_of_week='mon-fri', hour='9-18',
                           minute='2,7,12,17,22,27,32,37,42,47,52,57',
                           second='5', id=self.id, *args, **kwargs)

    def createJob(self, job_function):
        def func(*args, **kwargs):
            self.started.emit(job_function)
            job_function(*args, **kwargs)
            self.completed.emit(job_function)

        return func

    def start(self):
        self.sched.start()

    def next_occurance(self):
        for job in self.sched.get_jobs():
            if job.id == self.id:
                return job.next_run_time


if __name__ == '__main__':

    raise NotImplemented
