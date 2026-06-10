"""
y, 2020.1.23
pymongo - create index.py
"""

import pymongo

host = ['localhost:28000', '10.227.253.51:28000', '12.23.64.241:28000']
port = None
database = 'test_database'
collection = 'test_collection'
client = pymongo.MongoClient(host, port, tz_aware=True)
client_database = client[database]
client_collection = client_database[collection]
try:
    client_collection.create_index(
        [('createdAt', pymongo.ASCENDING)],
        name='createdAt', unique=False, expireAfterSeconds=86400)  # 10 days
    client_collection.create_index(
        [('mike', pymongo.DESCENDING), ('eliot', pymongo.ASCENDING)],
        name='test_index')
except Exception as ex:
    print(ex)

client.close()
