"""
y, 2022.4.25
python yield - recursive generator.py
"""


import itertools
import time


def generator_1(repeat, choices):
    for a in itertools.product(choices, repeat=repeat):
        yield a


def generator_2(repeat, choices):
    a = [None] * repeat

    def _inner(r, cs):
        if r < repeat:
            for k in cs:
                a[r] = k
                yield from _inner(r+1, choices)
        else:
            yield a

    yield from _inner(0, choices)


start_time = time.time()

repeat = 20
choices = [0, 1]

for j, seq in enumerate(generator_1(repeat, choices), start=1):
    # print(f"g1 {j=}: {seq=}")
    pass
print(f"time_lap={(time.time() - start_time)*1000:.3f}ms")  # time_lap=242.998ms

for j, seq in enumerate(generator_2(repeat, choices), start=1):
    # print(f"g1 {j=}: {seq=}")
    pass
print(f"time_lap={(time.time() - start_time)*1000:.3f}ms")  # time_lap=1849.008m
