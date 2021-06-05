"""
y, subprocess - new shell.py, 2019.7.25
https://docs.python.org/3/library/subprocess.html
https://stackoverflow.com/questions/2231227/python-subprocess-popen-with-a-modified-environment
"""


import subprocess
import os
import random
import multiprocessing as mp


def offspring():

    envs = os.environ
    index = random.randrange(0, 999)
    print('>>', index)
    subprocess.run(['subprocess - new shell.bat', 'arg1', str(index)], env={**envs, 'ZZ': str(index)})


if __name__ == '__main__':

    mp.freeze_support()

    processes = []
    for j in range(4):
        process = mp.Process(target=offspring)
        processes.append(process)
        process.start()

    for process in processes:
        process.join()
