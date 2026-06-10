"""
y, 2020.7.28
dask - access mongodb
https://github.com/dask/dask/issues/4873
"""

NotImplementedError('2020.7.28')

@dask.delayed
def q_to_list(q):
    mongo = pymongo.MongoClient(...)
    return (apply q to mongo client)
queries = [main_query + partition_clause(i) for i in range(npartitions)]  # may be kwargs, whatever you need

# for lists of objects
import dask.bag as db
bag = db.from_delayed([q_to_list(q) for q in queries])

# for dataframes
import dask.dataframe as dd
df = dd.from_delayed([q_to_list(q) for q in queries])  # optionally provide meta= if you expect a known df structure