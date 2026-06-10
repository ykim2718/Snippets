"""
y, pyMongo - eval 1st.py, 2017.3.8, 6.14 - 6.16

Environment
-----------
set path=%path%;c:\..\MongoDB\Server\3.4\bin

Open MongoDB
------------
mkdir c:\y\db
c:\..\MongoDB\Server\3.4\bin> mongod --dpath=c:\y\yydb --port 27017 -auth

Open mongo shell
----------------
mongo 12.23.31.250:27017

Set user and password in shell
------------------------------
> use admin
> db.createUser( {user: 'y", pwd: "yy", roles: [{role: "readWrite", db:"admin"}] } )
> ^C
>

"""

import sys
import pymongo
import datetime as dt

# connection = pymongo.MongoClient("pymongo://localhost")
connection = pymongo.MongoClient("12.23.31.250", 27057)
db = connection.db1  # database
c1 = db.collection1  # collection
doc = { '_id': dt.datetime.now(), 'say': 'Hello mongo !!!'}
try:
    c1.insert(doc)
except:
    print("insert failed", sys.exc_info()[0])



