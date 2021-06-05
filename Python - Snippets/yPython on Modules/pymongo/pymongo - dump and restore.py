"""
y, 2020.5.21 - 22, 5.27
pymongo - dump and restore.py

Objective
--------
# dump and restore sharded cluster which are prohibited since MongoDB 4.2+ [1]

Reference
---------
[1] https://docs.mongodb.com/manual/tutorial/backup-sharded-cluster-with-database-dumps/
[2] https://docs.python.org/3/library/struct.html

Note
----
# mongodump and mongorestore cannot be part of a backup strategy for 4.2+ sharded clusters that have sharded
  transactions in progress, as backups created with mongodump do not maintain the atomicity guarantees of
  transactions across shards [1].
"""

import pymongo
import pathlib
import pickle
import struct
import re
import datetime as dt
import zlib


class YMongoManager:
    """ y, 2020.5.21 - 22 """

    index_format = "LLL"  # size, sequence, total
    index_size = struct.calcsize(index_format)
    file_extension = 'ykl'
    compression_level = 9  # 0 to 9 or -1, -1 = Z_DEFAULT_COMPRESSION = equivalent to 6 [2]
    verbose = 1024*1
    client = None

    def __init__(self, host, file_extension=file_extension, compression_level=compression_level, verbose=verbose):
        """ y, 2020.5.21 - 22 """

        assert isinstance(host, str) and ':' in host, f"expected host like localhost:27017 but got {host}"
        assert isinstance(file_extension, str)
        assert -1 <= compression_level <= 9

        self.client = pymongo.MongoClient(host, tz_aware=True)
        self.file_extension = file_extension
        self.compression_level = compression_level
        self.verbose = verbose

    def dump(self, database_name, collection_name, dump_folder_path):
        """ y, 2020.5.21 - 22 """

        assert isinstance(database_name, (type(None), str))  # None for all
        assert isinstance(collection_name, (type(None), str))  # None for all
        assert isinstance(dump_folder_path, pathlib.Path)
        assert not dump_folder_path.is_file()

        if database_name is None:
            names = self.client.list_database_names()
            print(f"found database: {names}")
            dumped_file_paths = []
            for a_name in sorted(names):
                file_paths = self.dump(a_name, collection_name, dump_folder_path)
                dumped_file_paths += file_paths
            return dumped_file_paths

        if collection_name is None:
            names = self.client[database_name].list_collection_names()
            print(f"found '{database_name}' collection: {names}")
            dumped_file_paths = []
            for a_name in sorted(names):
                file_paths = self.dump(database_name, a_name, dump_folder_path)
                dumped_file_paths += file_paths
            return dumped_file_paths

        collection = self.client[database_name][collection_name]
        # dump_folder_path.mkdir(parents=True, exist_ok=True)
        folder_path = dump_folder_path / database_name
        folder_path.mkdir(parents=True, exist_ok=True)
        file_path = folder_path / f"{collection_name}.{self.file_extension}"
        with open(file_path, 'wb') as f:
            t = collection.count_documents({})
            print(f"dumping a collection: {database_name}.{collection_name}")
            for j, doc in enumerate(collection.find(), start=1):
                pickled = pickle.dumps(doc)
                zipped = zlib.compress(pickled, level=self.compression_level)
                zipped_size = len(zipped)
                index = struct.pack(self.index_format, zipped_size, j, t)
                if self.verbose and (j % self.verbose == 1 or j == t):
                    print(f"\t{j}/{t}={j/t:.1%}, size={zipped_size:,}, lap={dt.datetime.now() - start_time}")
                f.write(index)
                f.write(zipped)
        return [file_path]

    def restore(self, database_name, collection_name, a_path):
        """ y, 2020.5.21 - 22 """

        assert isinstance(database_name, (type(None), str))  # None for all
        assert isinstance(collection_name, (type(None), str))  # None for all
        assert isinstance(a_path, pathlib.Path)  # could be either a file or a folder
        assert a_path.exists(), f"cannot find a path: {a_path}"

        if database_name is None:
            database_name = str(a_path.parent)
        if collection_name is None:
            collection_name = a_path.stem

        if re.search('(\.|\$)', database_name):
            raise AttributeError(f"invalid characters (.$) in database name: {database_name}")
        if re.search('(\.|\$)', collection_name):
            raise AttributeError(f"invalid characters (.$) in collection name: {collection_name}")

        collection = self.client[database_name][collection_name]
        if a_path.is_dir():
            file_paths = list(a_path.glob(f"*.{self.file_extension}"))
        elif a_path.is_file():
            file_paths = [a_path]
        else:
            raise AssertionError

        if file_paths:
            print(f"found mongo db file with extension of {self.file_extension}: {len(file_paths)}")
        else:
            print(f"cannot find any files with extension of {self.file_extension}")
            return

        for file_path in file_paths:
            print(file_path)
            with open(file_path, 'rb') as f:
                f.seek(0, 2)  # jump to the end
                end_location = f.tell()
                f.seek(0)  # go back to the beginning
                while f.tell() < end_location:
                    index = f.read(self.index_size)
                    index = struct.unpack(self.index_format, index)
                    zipped = f.read(index[0])
                    pickled = zlib.decompress(zipped)
                    doc = pickle.loads(pickled)
                    j, t = index[1:]
                    try:
                        collection.insert_one(doc)
                    except Exception as ex:
                        print(f"{j}/{t}={j/t:.1%}, {ex.__class__.__name__}: {ex}")
                    else:
                        if self.verbose and (j % self.verbose == 1 or j == t):
                            print(f"{j}/{t}={j/t:.1%}, size={index[0]:,}, lap={dt.datetime.now() - start_time}")

    def restore_all(self):
        pass


if __name__ == '__main__':

    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('-host', type=str, default='10.227.253.51:29000')
    parser.add_argument('-database', '-d', type=str, default='test_database')  # * for all
    parser.add_argument('-collection', '-c', type=str, default='test_collection')  # * for all
    parser.add_argument('-a_path', '-folder', '-file', type=str, default=str(pathlib.Path(__file__).parent))
    parser.add_argument('-run', default='restore', choices=['dump', 'restore'])
    args = parser.parse_args()

    print(args)

    if args.database == '*':
        args.database = None
    if args.collection == '*':
        args.collection = None

    start_time = dt.datetime.now()
    mm = YMongoManager(args.host)
    a_path = pathlib.Path(args.a_path)
    if args.run == 'dump':
        mm.dump(args.database, args.collection, a_path)
    elif args.run == 'restore':
        mm.restore(args.database, args.collection, a_path)

    print(f"database={args.database}, collection={args.collection}, a_path={args.a_path}")
    print(f"ended at {dt.datetime.now()} running for {dt.datetime.now() - start_time}")




