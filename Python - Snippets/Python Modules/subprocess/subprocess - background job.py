"""
y, 2022.9.12, 12.20
subprocess - background job.py
"""

import subprocess
import sys
import time

print(__name__, 'before Popen')
p = subprocess.Popen([sys.executable, "child.py"], shell=True)
if False:
    out = p.communicate()
    print(f"{out=}")
time.sleep(5)  # subprocess killed when manin process is terminated !!! 2022.12.20
print(__name__, 'after Popen')
