"""
y, 2022.1.21
pymongo - rs.status().py
https://stackify.dev/310011-get-replicationlag-in-mongo-with-pymongo
"""

import pymongo
import time
from bson.codec_options import DEFAULT_CODEC_OPTIONS

codec_options = DEFAULT_CODEC_OPTIONS.with_options(unicode_decode_error_handler='ignore')

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

server = servers['S1']
for key, value in replicas.items():
    # url = f"mongodb://{server}:{value}/?replicaSet={key}"
    url = f"mongodb://{server}:{value}"
    print(f"replica={key}")
    print(f"url={url}")
    client = pymongo.MongoClient(url, replicaset=key)
    time.sleep(0.1)
    print(f"client.nodes={client.nodes}")
    status = client.admin.command('replSetGetStatus', codec_options=codec_options)
    # status = client['admin'].command({'replSetGetStatus': 1}, codec_options=codec_options)
    for member in status['members']:
        print('\t', member['name'], member['stateStr'])
