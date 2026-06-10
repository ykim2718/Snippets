"""
y, gc - 1st eval.py, 2016.6.10
"""

import gc
import atexit


def print_gc_collect():
    collected = gc.collect()
    print('Garbage collector: collected %d objectes.' % collected)


atexit.register(print_gc_collect)

print_gc_collect()

a_list = []
print(len(gc.get_referrers(a_list)))

# circular reference or reference cycle, see below,
# one fundamental flaw with reference counting
a_list.append(a_list)

print(len(gc.get_referrers(a_list)))
del a_list

print_gc_collect()
