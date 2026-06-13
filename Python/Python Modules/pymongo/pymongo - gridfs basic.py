"""
y, 2020.4.29 - 30
pymongo - gridfs basic.py
https://api.mongodb.com/python/current/examples/gridfs.html#saving-and-retrieving-data
https://api.mongodb.com/python/current/api/gridfs/index.html
"""

from pymongo import MongoClient
import gridfs

db = MongoClient('mongodb://10.0.0.20:27017').test_database
# db = MongoClient('mongodb://localhost:27017').test_database
fs = gridfs.GridFS(db, collection='fs')
fs_exists = fs.find_one({})
print(f"fs_exists={fs_exists}")
if True:  # write and read
    a = fs.put(b"hello world", **dict(a='abc', b='def'))
    b = fs.get(a).read()
    # TODO 2020.4.30, How to read other key-values, like b='def' ????
    print(b)
else:  # find and read
    founds = fs.find(dict(a='abc'), no_cursor_timeout=True)
    for found in founds:
        print(found.read())
