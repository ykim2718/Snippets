"""
y, 2022.9.12
subprocess - background job.py
"""

import subprocess

print('before Popen')
proc = subprocess.Popen(["c:\y\Anaconda3\python.exe", "child.py"], shell=True)
if False:
    out = proc.communicate()
    print(f"{out=}")
print('after Popen')
