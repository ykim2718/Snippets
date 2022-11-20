"""
y, 2022.11.20
celery - client.py
https://docs.celery.dev/en/stable/
"""

import importlib
import celery


task = importlib.import_module('celery - worker')

worker = task.background.delay('celery!')
print(f"{worker.id=}")

if False:
    while not worker.read():
        time.sleep(1)
        print(f"{worker.status=}")
    print(f"{worker.get(timeout=1)=}")
else:
    try:
        print(f"{worker.get(timeout=1)=}")
    except celery.exceptions.TimeoutError as ex:
        print(f"{ex=}")
        print(f"{worker.get(timeout=9)=}")
