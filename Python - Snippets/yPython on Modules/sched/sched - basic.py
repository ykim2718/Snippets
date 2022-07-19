"""
y, 2022.7.19
sched - basic.py
https://docs.python.org/3/library/sched.html
"""

import sched, time

s = sched.scheduler(time.time, time.sleep)


def print_time(a='default'):
    print(time.ctime(), f"{len(s.queue)=}, {a=}")


print(time.ctime(), 'started')
s.enter(10, 1, print_time)
s.enter(5, 2, print_time, argument=('2nd',))
s.enter(5, 1, print_time, kwargs={'a': '1st'})
s.run()
print(time.ctime())
