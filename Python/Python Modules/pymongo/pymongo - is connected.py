"""
y, pymongo - is connected.py, 2018.8.5
"""

import pymongo

client = pymongo.MongoClient('localhost', 27017, serverselectiontimeoutms=10000)  # 10 sec, while default is 30 sec
print(client)
print(client.server_info())
# print(client.list_database_names())

client.close()



