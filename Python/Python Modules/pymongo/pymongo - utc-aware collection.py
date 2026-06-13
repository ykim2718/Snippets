"""
y, 2020.1.16, 1.19
pymongo - utc-aware collection.py
https://api.mongodb.com/python/current/examples/datetimes.html
https://spoqa.github.io/2019/02/15/python-timezone.html  ★
"""

import pymongo
import pytz
import bson
import datetime as dt
import pprint

# client = pymongo.MongoClient('10.0.0.51', 28000)
client = pymongo.MongoClient('localhost', 27017)
test_database = client.test_database

TZ_SEOUL_BY_PYTZ = pytz.timezone('Asia/Seoul')
TZ_SEOUL_BY_DATETIME = dt.timezone(dt.timedelta(hours=9))
TZ_SEOUL = TZ_SEOUL_BY_DATETIME  # KST, https://en.wikipedia.org/wiki/Time_in_South_Korea

# codec_options = bson.codec_options.CodecOptions(tz_aware=True, tzinfo=TZ_SEOUL_BY_PYTZ)
codec_options = bson.codec_options.CodecOptions(tz_aware=True, tzinfo=TZ_SEOUL_BY_DATETIME)
test_collection = test_database.test_collection.with_options(codec_options=codec_options)

doc = {
    '_id': 'Hello Mongo UTC !!!',
    'str(dt_datetime_now())': str(dt.datetime.now()),
    'dt_datetime_now()': dt.datetime.now(),  # WRONG
    'dt_datetime_now(tz=TZ_SEOUL_BY_DATETIME)': dt.datetime.now(tz=TZ_SEOUL_BY_DATETIME),  # RIGHT
    'TZ_SEOUL_BY_PYTZ_localize(dt_datetime_now())': TZ_SEOUL_BY_PYTZ.localize(dt.datetime.now()),  # RIGHT
}

result = test_collection.insert_one(doc)
doc = test_collection.find_one({'_id': doc['_id']})
print(pprint.pformat(doc, indent=2, width=128))
a_time = doc['dt_datetime_now(tz=TZ_SEOUL_BY_DATETIME)']
print(a_time, type(a_time), f"utcoffset={a_time.tzinfo.utcoffset(a_time)}")

"""
{ 'TZ_SEOUL_BY_PYTZ_localize(dt_datetime_now())': datetime.datetime(2020, 1, 19, 19, 48, 58, 826000, tzinfo=datetime.timezone(datetime.timedelta(0, 32400))),
  '_id': 'Hello Mongo UTC !!!',
  'dt_datetime_now()': datetime.datetime(2020, 1, 20, 4, 48, 58, 826000, tzinfo=datetime.timezone(datetime.timedelta(0, 32400))),
  'dt_datetime_now(tz=TZ_SEOUL_BY_DATETIME)': datetime.datetime(2020, 1, 19, 19, 48, 58, 826000, tzinfo=datetime.timezone(datetime.timedelta(0, 32400))),
  'str(dt_datetime_now())': '2020-01-19 19:48:58.826914'}
2020-01-19 19:48:58.826000+09:00 <class 'datetime.datetime'> utcoffset=9:00:00
"""


