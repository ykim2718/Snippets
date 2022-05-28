"""
y, 2022.5.28
contextvars - basic.py
https://ryanking13.github.io/2018/07/12/python-37-whats-new.html
"""

import contextvars


def show():
    print('value is', val.get())


# context variable인 'val'을 생성
val = contextvars.ContextVar("val", default=0)
contexts = list()

for _ in range(5):
    # 현재 context의 복사본을 받아서
    ctx = contextvars.copy_context()

    # 해당 context에서의 val 값을 업데이트
    ctx.run(val.set, val.get() + 1)

    contexts.append(ctx)

for ctx in contexts:
    ctx.run(show)
