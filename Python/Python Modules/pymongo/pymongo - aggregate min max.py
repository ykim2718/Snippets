"""
y, 2020.1.19
pymongo - aggregate min max.py
"""

import pymongo
import pprint

host_and_port = dict(host='10.0.0.51', port=28000)
database_name = 'pa_fab'
collection_name = 'cp_chip_para'

client = pymongo.MongoClient(**host_and_port, tz_aware=True)
database = client[database_name]
collection = database[collection_name]

pipeline = [
    {
        '$group':
            {
                '_id': '$line_id',
                'min_tkout_time': {'$min': '$tkout_time'},
                'max_tkout_time': {'$max': '$tkout_time'},
                'count': {'$sum': 1}
            }
    }
]
result = collection.aggregate(pipeline)
result = list(result)
print(pprint.pformat(result, indent=2, width=128))

a_time = result[-1]['max_tkout_time']
print(a_time, type(a_time), f"utcoffset={a_time.tzinfo.utcoffset(a_time)}")
