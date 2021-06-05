"""
Y. Kim, 2016.4.10
"""

d = {'banana': 4, 'apple': 3, 'pear': 1, 'orange': 2}

print("Dictionary sorted by key .....")
for key in sorted(d, key=lambda x: x):  # same as x[0]
    print("%s: %s" % (key, d[key]))

print("Dictionary sorted by 1/len(key) ...")
for key in sorted(d, key=lambda x: 1 / len(x)):
    print("%s: %s" % (key, d[key]))

print("Dictionary sorted by value .....")
for key in sorted(d, key=d.get):  # same as get('value')
    print("%s: %s" % (key, d[key]))


def GetSortedKeysOfDictByKey(Dic, bReverse=False):
    for key in sorted(Dic, key=lambda x: x, reverse=bReverse):
        yield key


def GetSortedKeysOfDictByKeyLen(Dic, bReverse=False):
    for key in sorted(Dic, key=lambda x: len(x), reverse=bReverse):
        yield key


def GetSortedKeysOfDictByValue(Dic, bReverse=False):
    for key in sorted(Dic, key=Dic.get, reverse=bReverse):
        yield key


print("Dictionary sorted by GetSortedKeysOfDictByKey()")
Keys = GetSortedKeysOfDictByKey(d)
for key in Keys: print(key, ":", d[key])

print("Dictionary sorted by GetSortedKeysOfDictByKeyLen()")
Keys = GetSortedKeysOfDictByKeyLen(d)
for key in Keys: print(key, ":", d[key])

print("Dictionary sorted by GetSortedKeysOfDictByValue( reverse=true )")
Keys = GetSortedKeysOfDictByValue(d, True)
for key in Keys: print(key, ":", d[key])
