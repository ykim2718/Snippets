"""
y, generator - class (2).py, 2019.10.18, 10.20
"""


class Generator:

    def __init__(self, stones):
        self.stones = stones
        self.index = -1

    def __iter__(self):
        self.index = -1
        return self

    def __next__(self):
        self.index += 1
        if self.index < len(self.stones):
            result = self.stones[self.index]
            return result
        else:
            raise StopIteration


g = Generator([1, 2, 3])

for j in g:
    print(j)
print(list(g))
for j in g:
    print(j)
