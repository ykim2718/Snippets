"""
y, 2020.3.9
datetime - for loop corresponding to 1 second.py
"""

import datetime as dt

start_time = dt.datetime.now()
for j in range(int(3.45e7)):
    pass
run_time = dt.datetime.now() - start_time
print(run_time)