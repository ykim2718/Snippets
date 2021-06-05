"""
y, 2020.2.21
python yield - __iter__.py
"""


class Klass:

    def __init__(self):

        self.a = [1, 2, 3]

    def __len__(self):
        return len(self.a)

    def __getitem__(self, index):
        return self.a[index]

    def __iter__(self):

        if True:
            for j in range(len(self)):
                yield self[j]
        else:
            for item in (self[j] for j in range(len(self))):
                yield item


k = Klass()
for j in k:
    print(j)
print(k[0], k[1], k[2])
