"""
y, 2016.8.5, tracemalloc.py
"""
import tracemalloc

tracemalloc.start()


def test():
    a = [1] * 2
    a = [a]
    return b


snapshot1 = tracemalloc.take_snapshot()
test()
snapshot2 = tracemalloc.take_snapshot()

top_stats = snapshot2.compare_to(snapshot1, 'lineno')

print('[ Top 10 differences ]')
for stat in top_stats[:10]:
    print(stat)
