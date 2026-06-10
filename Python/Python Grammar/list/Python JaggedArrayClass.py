"""
Iterating over a custom ‘Jagged Array’ in Python
http://gauravpandey.com/wordpress/?p=535
"""


class JaggedArray(list):
    ''' An array of arrays! '''

    def __iter__(self):
        if self:
            ptr = len(self) - 1
            count = 0

            while count <= ptr:
                item = self[count]

                if isinstance(item, (tuple, list,)):
                    newPtr = len(item) - 1
                    newCount = 0

                    while newCount <= newPtr:
                        newItem = item[newCount]
                        yield newItem
                        newCount += 1
                else:
                    yield item

                count += 1


def main():
    obj = JaggedArray()
    obj.append((1, 2, 3,))
    obj.append([4, 5, 6, 7])
    obj.append((8, 9,))

    for item in obj:
        print(item, )

    print(obj)


if __name__ == '__main__':
    main()
