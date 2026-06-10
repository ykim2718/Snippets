"""
y, pymongo - parse_uri.py, 2018.5.16 - 17, 12.26
https://docs.mongodb.com/manual/reference/connection-string/#examples
http://api.mongodb.com/python/current/api/pymongo/uri_parser.html
"""

import pymongo

url = 'mongodb://sysop:moon@12.23.34.45:28000/database.collection'
url = 'mongodb://db1.example.net:27017,db2.example.net:2500/?replicaSet=test&key=value'
# url = 'pymongo://sysopmoon12.23.34.4528000records'

r = pymongo.uri_parser.parse_uri(url, validate=False)
print(r)