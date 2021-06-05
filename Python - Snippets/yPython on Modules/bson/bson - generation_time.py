"""
y, 2020.10.2
bson - generation_time.py
https://api.mongodb.com/python/current/api/bson/objectid.html
"""

import bson
import datetime as dt

now = dt.datetime.now()
print(now)
my_id = bson.ObjectId.from_datetime(now)
print(my_id)
print(my_id.generation_time)

"""
2020-10-02 19:43:54.492037
5f7782fa0000000000000000
2020-10-02 19:43:54+00:00
"""