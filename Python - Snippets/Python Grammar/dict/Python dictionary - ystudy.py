print('y, 2016 March')

dic = {
    'a': 1,
    'b': 2,
    'c': 3
}
for k in dic.keys():
    print(k)

print('y, 2016 April')
dic_val = {
    'a': lambda x: x ** 2,
    'b': 2,
    'c': 3
}['a'](2)
print(dic_val)

print('y, 2016.6.1')
choices = {
    1: 10,
    2: 20,
    -1: -10
}
r = choices.get(23, 'others')
print(r)
print(choices[-1])

print('y, 2016.6.1, how to return dictionary keys as a list')
print("list(choices)=", list(choices))

print('y, 2016.7.15')
a_dict = dict(key1='value1', key2='value2')
print(a_dict, a_dict['key1'])
