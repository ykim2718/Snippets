"""
y, pymongo - benchmark batch insert.py, 2018.10.18; 2020.1.19, 1.22, 2.13
"""

import pymongo
import datetime as dt

host = 'localhost'
host = '10.0.0.51'
port = 28000
TZ_SEOUL = dt.timezone(dt.timedelta(hours=9))
database = 'test_database'
collection = 'test_collection'
client = pymongo.MongoClient(host, port, tz_aware=True)
client_database = client[database]
client_collection = client_database[collection]

try:
    _createdAt = 'createdAt'
    client_collection.create_index([(_createdAt, pymongo.ASCENDING)], name=_createdAt, unique=False,
                                   expireAfterSeconds=10 * 24 * 3600)
except pymongo.errors.OperationFailure as ex:
    print(ex)

doc_count = int(1e6)

for case in [
    'ordered_insert_many(many_small_docs)', 'ordered_bulk_write(many_small_docs)',
    'unordered_insert_many(many_small_docs)', 'unordered_bulk_write(many_small_docs)',
    'unordered_insert_many(few_big_docs)'
]:
    start_time = dt.datetime.now()
    if case in ['ordered_insert_many(many_small_docs)', 'unordered_insert_many(many_small_docs)']:
        docs = [dict(number=j, createdAt=dt.datetime.now(tz=TZ_SEOUL)) for j in range(doc_count)]
        client_collection.insert_many(docs, ordered=(case == 'ordered_insert_many(many_small_docs)'))
    elif case in ['ordered_bulk_write(many_small_docs)', 'unordered_bulk_write(many_small_docs)']:
        docs = [pymongo.InsertOne(dict(number=j, createdAt=dt.datetime.now(tz=TZ_SEOUL))) for j in range(doc_count)]
        client_collection.bulk_write(docs, ordered=(case == 'ordered_bulk_write(many_small_docs)'))
    elif case == 'unordered_insert_many(few_big_docs)':
        doc_group_size = int(1e3)  # key-value count per doc
        count = doc_count // doc_group_size
        docs = []
        for k in range(count):
            docs.append(dict({str(j): j for j in range(doc_group_size)}, **{'createdAt': dt.datetime.now(tz=TZ_SEOUL)}))
            for j in range(doc_group_size):
                dt.datetime.now()
        client_collection.insert_many(docs, ordered=False)
    run_time = dt.datetime.now() - start_time
    print("%s run time =" % case, run_time)

client.close()

