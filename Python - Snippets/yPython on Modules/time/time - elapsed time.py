"""
y, 2020.3.5
time - elapsed time.py
"""

import time

start_time = time.time()
time.sleep(1)
elapsed_time = time.time() - start_time
elapsed_str = time.strftime("%H:%M:%S", time.gmtime(elapsed_time))
print(elapsed_str)