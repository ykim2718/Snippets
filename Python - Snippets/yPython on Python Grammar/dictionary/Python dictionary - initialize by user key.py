"""
y, Python dictionary - initialize by user key.py, 2017.12.17
"""


def get_dict_of_key_in_a_nested_dictionary(dictionary, key):
    """
    y, 2017.12.17

    Usage
    -----

    >> a_dict = {'a': {'b': {'bb': 22},
    >>                 'c': 3,
    >>                 '@init': 'd'},
    >>           'd': 4,
    >>           '@init': 'a.b'}
    >> for j, (dic , key) in enumerate(get_dict_of_key_in_a_nested_dictionary(a_dict, '@init'), start=1):
    >>     print(j, dic, key, '>>', dic[key])
           1 {'c': 3, 'b': {'bb': 22}, '@init': 'd'} @init >> d
           2 {'d': 4, 'a': {'c': 3, 'b': {'bb': 22}, '@init': 'd'}, '@init': 'a.b'} @init >> a.b

    """

    for k, v in dictionary.items():
        if k == key:
            yield dictionary, key
        elif isinstance(v, dict):
            yield from get_dict_of_key_in_a_nested_dictionary(v, key)


# function below copied from yData.py
def get_dict_of_dotted_key_in_a_nested_dictionary(dictionary, dotted_key):
    """ y, 2017.7.14, 12.17 """

    head, _, tail = dotted_key.partition('.')
    if bool(tail):
        return get_dict_of_dotted_key_in_a_nested_dictionary(dictionary[head], tail)
    else:
        if dotted_key in dictionary:
            return dictionary, dotted_key
        else:
            return None, None


a_dict = {'a': {'b': dict(bb=22),
                'c': 3,
                '@init': 'd'},
          'd': 4,
          '@init': 'a.b',
          # '@init': 'a.d',
          }
print(a_dict)

for j, (dic , key)in enumerate(get_dict_of_key_in_a_nested_dictionary(a_dict, '@init'), start=1):
    d, k = get_dict_of_dotted_key_in_a_nested_dictionary(a_dict, dic[key])
    print(j, dic, key, '>>', dic[key], '\n\t', d, k, '>>', d[k] if d and k else None)


