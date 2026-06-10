"""
y, 2022.7.25
python yield - class generator
https://stackoverflow.com/questions/42983569/how-to-write-a-generator-class
"""


class MyNumbers:
    def __init__(self, start=0, stop=3):
        self.start = start
        self.stop = stop
        self.generator_iterator = self.generator()

    def __iter__(self):
        return self

    def __next__(self):
        return next(self.generator_iterator)

    def generator(self):
        for j in range(self.start, self.stop):
            yield j


g = MyNumbers()
for k in g:
    print(k)
