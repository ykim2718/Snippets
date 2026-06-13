"""
y, 2020.1.23
pymongo - connect multi-hosts.py
"""

import pymongo

host = 'localhost'
port = 27017
host = ['localhost:28000', '10.0.0.51:28000', '198.51.100.1:28000']
port = None
database = 'test_database'
collection = 'test_collection'
client = pymongo.MongoClient(host, port, tz_aware=True)
client_database = client[database]
client_collection = client_database[collection]
host = client_database.command('serverStatus')['host']
print(f"host={host}")
print(f"localTime={client_database.command('serverStatus')['localTime']}")
print(f"sharding={client_database.command('serverStatus')['sharding']}")
print(f"doc_count={client_collection.estimated_document_count()}")

client.close()
