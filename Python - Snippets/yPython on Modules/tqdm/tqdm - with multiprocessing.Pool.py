"""
y, 2021.9.19
tqdm - with multiprocessing.Pool.py
https://github.com/tqdm/tqdm/issues/484
https://stackoverflow.com/questions/41920124/multiprocessing-use-tqdm-to-display-a-progress-bar
"""

import time
import random
from multiprocessing import Pool
from tqdm import tqdm


def myfunc(a):
    time.sleep(random.random())
    return a ** 2


if __name__ == '__main__':
    # freeze_support()

    pool = Pool(2)
    '''
    for _ in tqdm(pool.imap_unordered(myfunc, range(100)), total=100):
        pass
    '''
    pbar = tqdm(total=100)


    def update(*a):
        pbar.update()
        # tqdm.write(str(a))


    for i in range(pbar.total):
        pool.apply_async(myfunc, args=(i,), callback=update)
    # tqdm.write('scheduled')
    pool.close()
    pool.join()
