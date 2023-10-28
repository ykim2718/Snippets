"""
y, 2023.10.27
pymongo - bulk_write.py
https://www.mongodb.com/docs/manual/reference/method/db.collection.bulkWrite/
https://pymongo.readthedocs.io/en/stable/examples/bulk.html
"""

import pymongo
import pprint

client = pymongo.MongoClient("mongodb://localhost:27017")
# client = pymongo.MongoClient("localhost", 27017)
db = client.test_database  # database
dc = db.test_collection  # collection

# requests = [pymongo.InsertOne({'_id': j, 'key': 0}) for j in range(5)]
requests = [pymongo.UpdateOne({'_id': j}, {'$set': {'key': j*10}}) for j in range(5)]

try:
    result = dc.bulk_write(requests, ordered=False)
except pymongo.errors.BulkWriteError as e:
    pprint.pprint(e.details)
else:
    pprint.pprint(result.bulk_api_result)
