"""
y, python class - array shell indexable.py, 2019.2.27 - 28
"""


class YArrayShellIndexable:
    """ y, 2019.2.27 - 28 """

    def __init__(self, caller, length, index_method='loc'):
        """ y, 2019.2.27 - 28 """

        assert callable(caller)
        assert index_method in ['loc', 'iloc']
        self.caller = caller
        self.length = length

    def __len__(self):
        """ y, 2019.2.27 """

        return self.length

    def __getitem__(self, index):
        """ y, 2019.2.27 - 28 """

        if isinstance(index, (int, list, slice)):
            return self.caller(index)
        else:
            raise IndexError(index)


import functools
import pandas as pd


array = pd.Series([10, 20, 30], index=list('abc'))


def f(j, a):

    return a.iloc[j]


c = functools.partial(f, a=array)


index_method = 'iloc'
shell = YArrayShellIndexable(c, len(array), index_method=index_method)

print('len(shell)=', len(shell))
if index_method == 'loc':
    print(shell[['a', 'b']])
elif index_method == 'iloc':
    print(shell[[0, 1]])
    print(shell[slice(-1)])
    print(shell[1:2])
    print(shell[-1])

