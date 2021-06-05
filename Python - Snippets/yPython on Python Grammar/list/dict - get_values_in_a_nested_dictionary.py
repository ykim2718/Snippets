"""
y, get_values_in_a_nested_dictionary.py, 2017.7.17

"""

import re

def get_values_in_a_nested_dictionary(a_dict, keys):
    """ y, 2017.7.17 """

    assert isinstance(keys, list) and len(keys) >= 1

    if len(keys) > 1:
        values = []
        if isinstance(a_dict, (dict, list)):
            for key in list(a_dict):
                if re.match(keys[0], key):
                    if a_dict.get(key, False):
                        values += get_values_in_a_nested_dictionary(a_dict[key], keys[1:])
        return values
    else:
        values = []
        if isinstance(a_dict, dict):
            for key in list(a_dict):
                if re.match(keys[0], key):
                    values.append(a_dict[key])
        return values

a_dict = {
    'first': 11,
    'first1': {
        'second': {
            'third': 3,
            'third1': 4
        },
        'second1': 5,
        '2nd': 25
    },
    'first2': 12}
print(a_dict)

# values = get_values_in_a_nested_dictionary(a_dict, 'f\w+'.split('.'))
values = get_values_in_a_nested_dictionary(a_dict, 'f\w+.\w+'.split('.'))
# values = get_values_in_a_nested_dictionary(a_dict, 'f\w+.\w+.third\w*'.split('.'))
# values = get_values_in_a_nested_dictionary(a_dict, 'f\w+.second.third$'.split('.'))
# values = get_values_in_a_nested_dictionary(a_dict, 'first1.second.third'.split('.'))
# values = get_values_in_a_nested_dictionary(a_dict, 'first.(second\d?|2nd)'.split('.'))
print(values)
