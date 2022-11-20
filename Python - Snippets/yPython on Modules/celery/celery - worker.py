"""
y, 2022.11.20
celery - worker.py
https://docs.celery.dev/en/stable/
"""

from celery import Celery
import time


# celery -A "celery - worker" worker --pool=solo --loglevel=info

app = Celery(
    'task',
    backend='redis://localhost/0',
    broker='redis://localhost/0',
)


@app.task()
def background(x):

    print('task running ...')
    time.sleep(5)
    print('.. ended task')

    return f"Hello .. {x}"


# data = background.delay('celery')
# from celery.result import AsyncResult
#   id = 'xxx
#   res = AsyncResult(id
#   res.get()