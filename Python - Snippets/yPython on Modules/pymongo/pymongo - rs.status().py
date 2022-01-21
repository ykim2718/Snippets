"""
y, 2022.1.21
pymongo - rs.status().py
https://stackify.dev/310011-get-replicationlag-in-mongo-with-pymongo
"""

import pymongo
import time
from bson.codec_options import DEFAULT_CODEC_OPTIONS

code_options = DEFAULT_CODEC_OPTIONS.with_options(unicode_decode_error_handler='ignore')
servers = dict(
    S1='10.227.253.174',
    S2='10.227.253.148',
    S3='10.227.253.214',
    S4='10.227.253.136',
)
replicas = dict(
    PASystem_mongodb_shard_s1=28001,
    PASystem_mongodb_shard_s2=28002,
    PASystem_mongodb_shard_s3=28003,
)

for key, value in replicas.items():
    # uri = f"mongodb://{servers['S2']}:{value}/?replicaSet={key}"
    uri = f"mongodb://{servers['S2']}:{value}"
    print(f"replica={key}")
    print(f"uri={uri}")
    client = pymongo.MongoClient(uri, replicaset=key)
    time.sleep(0.1)
    print(f"client.nodes={client.nodes}")
    status = client.admin.command('replSetGetStatus', codec_options=code_options)
    # status = client['admin'].command({'replSetGetStatus': 1}, codec_options=code_options)
    for member in status['members']:
        print('\t', member['name'], member['stateStr'])
