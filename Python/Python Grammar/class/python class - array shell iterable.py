"""
y, python class - array shell iterable.py, 2019.2.27 - 28
"""


class YArrayShellIterable:
    """ y, 2019.2.27 """

    def __init__(self, generator, length):

        assert hasattr(generator, '__iter__')
        self.generator = generator
        self.length = length

    def __len__(self):

        return self.length

    def __iter__(self):

        return self.generator

    def __eq__(self, other):

        raise NotImplementedError()

    def __contains__(self, item):

        raise NotImplementedError()

    def __getitem__(self, index):

        raise IndexError(index)


g = iter('abc')
shell = YArrayShellIterable(g, 2)
print(len(shell), list(shell))
# print(shell[[0, 1]])
# print(shell[-1])
# print(shell[1:2])

