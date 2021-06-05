"""
y, 2020.5.16 - 17, 5.20
pymongo - $inc date.py
https://jira.mongodb.org/browse/SERVER-3174  << Allows $inc for Date
https://docs.mongodb.com/manual/reference/operator/aggregation/dateToParts/
"""

import pymongo
import pandas as pd

host_and_port = dict(host='localhost', port=27017)
client = pymongo.MongoClient(**host_and_port, tz_aware=True)
database = client['test_database']
collection = database['test_collection']

if False:
    query = {}
    # update = {'$inc': {'date': 1*9*60*60*1000}}  # pymongo.errors.WriteError: Cannot apply $inc to a value of non-numeric type.
    update = [{'$set': {'date': {'$add': ['$date', -1*9*60*60*1000]}}}]  # naive time to seoul time by adding -9 hours
    result = collection.update_one(query, update)
    print(result)
else:
    host_and_port = dict(host='localhost', port=27017)
    client = pymongo.MongoClient(**host_and_port, tz_aware=True)
    database = client['yFMeasureKorea']
    collection = database['stock_pb_day']  # stock_pb_day, stock_short_selling, stock_pb_minute
    target_key = 'date'
    temporary_collection_name = '_naive_time'
    if database[temporary_collection_name].count_documents({}):
        database.drop_collection(temporary_collection_name)
        print(f"found and dropped temporary collection: {temporary_collection_name}")
    pipeline = [
        {'$project': {'parsed_date': {'$dateToParts': {target_key: f"${target_key}"}}}},
        {'$match': {'parsed_date.hour': 0}},
        {'$project': {'_id': 1}},
        {'$out': temporary_collection_name},
    ]
    collection.aggregate(pipeline)
    result = database[temporary_collection_name].find({}, no_cursor_timeout=True)
    t = database[temporary_collection_name].count_documents({})
    print(f"found {t} documents")
    update = [{'$set': {target_key: {'$add': [f"${target_key}", -1 * 9 * 60 * 60 * 1000]}}}]  # change naive time to seoul time
    for j, query in enumerate(result, start=1):
        print(f"{j}/{t}={j/t:.1%} _id={query['_id']}", end=' ')
        try:
            a_doc = collection.find_one_and_update(query, update)  # type(naive_date) == dict
            print(a_doc['date'])
        except pymongo.errors.DuplicateKeyError as ex:
            collection.delete_one(query)
            print('removed document due to the duplicated key that is going to be updated')
    database.drop_collection(temporary_collection_name)
