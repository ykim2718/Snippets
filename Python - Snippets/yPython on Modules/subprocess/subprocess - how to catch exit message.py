"""
y, subprocess - how to catch exit message.py, 2019.7.31
"""


import os
import sys
import subprocess


args = [sys.executable, 'child.py']

if False:
    with subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=1, universal_newlines=True,
                          cwd=os.getcwd()) as p:
        for line in p.stdout:
            print('[parent:stdout]', line.rstrip('\n'))
        if p.stderr:
            for line in p.stderr:
                print('[parent:stderr]', line.rstrip('\n'))
else:
    p = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, cwd=os.getcwd())
    print('[parent:stderr]', p.stderr)

print("[parent] vars(p) = {}".format(vars(p)))
print("[parent] p.returncode = {}".format(p.returncode))

