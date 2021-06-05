"""
y, 2020.2.11
dask - run in parallel.py,
https://examples.dask.org/applications/embarrassingly-parallel.html
https://docs.python.org/2/library/multiprocessing.html#windows  << Safe importing of main module
"""

# TODO 2020.2.11, Fix broken pipe error at the end of execution !!!

from dask.distributed import Client, progress
import time
import random
import pandas as pd
import numpy as np
import dask
import dask.bag as db


def costly_simulation(list_param):
    time.sleep(random.random())
    return sum(list_param)


if __name__ == '__main__':

    client = Client(threads_per_worker=4, n_workers=1)
    print(client)

    input_params = pd.DataFrame(np.random.random(size=(500, 4)),
                                columns=['param_a', 'param_b', 'param_c', 'param_d'])
    print(input_params.head())

    case = 'delayed'  # Using Dask DeLayed to make our function lazy
    case = 'futures'  # Using the Future API
    case = 'map'  # Using the Future API with map
    case = 'bag'  # Handling very large simulation with Bags

    if case == 'delayed':
        lazy_results = []
        for parameters in input_params.values:
            lazy_result = dask.delayed(costly_simulation)(parameters)
            lazy_results.append(lazy_result)
        futures = dask.persist(*lazy_results)  # trigger computation in the background
        client.cluster.scale(10)  # ask for ten 4-thread workers
        results = dask.compute(*futures)
        print(results[:5])
    elif case == 'futures':
        futures = []
        for parameters in input_params.values:
            future = client.submit(costly_simulation, parameters)
            futures.append(future)
        results = client.gather(futures)
        print(results[:5])
    elif case == 'map':
        futures = client.map(costly_simulation, input_params.values)
        results = client.gather(futures)
        print(results[:5])
    elif case == 'bag':
        b = db.from_sequence(list(input_params.values), npartitions=100)
        b = b.map(costly_simulation)
        results = b.compute()
        print(type(results))

    output = input_params.copy()
    output['result'] = pd.Series(results, index=output.index)
    print(output.sample(5))  # pd.sample(): Return a random sample of items from an axis of object.


