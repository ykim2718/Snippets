"""
y, 2021.9.19, 9.21 (추석날)
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


def update(*a):
    pbar.update()
    # tqdm.write(str(a))


if __name__ == '__main__':
    # freeze_support()

    pool = Pool(2)

    if False:
        for _ in tqdm(pool.imap_unordered(myfunc, range(100)), total=100):
            pass
        # tqdm.write('scheduled')
        pool.close()
        pool.join()

    else:
        aync_results = []
        pbar = tqdm(total=100)
        for i in range(pbar.total):
            r = pool.apply_async(myfunc, args=(i,), callback=update)
            aync_results.append(r)
        tqdm.write('scheduled')
        pool.close()
        pool.join()
        results = [p.get() for p in aync_results]
        print(f"results={results}")
        print(f"len(results)={len(results)}")

