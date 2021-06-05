"""
y, Python - dictionary with multi keyts to one value.py, 2016.6.13
http://stackoverflow.com/questions/10123853/how-do-i-make-a-dictionary-with-multiple-keys-to-one-value
"""

alias = {
    'a': 'id1',
    'b': 'id1',
    'c': 'id2',
    'd': 'id2'
}

dict = {
    'id1': 1,
    'id2': 2
}

print(dict[alias['a']])


def add(key, id, value=None):
    if id in dict:
        if key in alias:
            # Do nothing
            pass
        else:
            alias[key] = id
    else:
        dict[id] = value
        alias[key] = id


add('e', 'id2')
add('f', 'id3', 3)

print(dict[alias['f']])
