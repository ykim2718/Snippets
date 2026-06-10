"""
y, 2020.2.24
gc - basic.py
https://wikidocs.net/13969
"""

import sys, gc


def delete_me(obj):
    referrers = gc.get_referrers(obj)
    for referrer in referrers:
        if type(referrer) == dict:
            for key, value in referrer.items():
                if value is obj:
                    referrer[key] = None


def test():
    class A:
        def __del__(self):
            print("deleted")

    class B:
        def __init__(self, obj):
            self.obj = obj

    a = A()
    b = B(a)

    print("before : ", b.__dict__)
    delete_me(a)
    print("after : ", b.__dict__)
    print("ref count : ", sys.getrefcount(a))
    gc.collect()
    print("ref count : ", sys.getrefcount(a))
    del (a)


test()
