"""
y, Python - dict compare keys in nested dict.py, 2017.8.14

"""

def get_listed_keys_in_a_nested_dictionary(a_dict):
    """ y, 2017.8.14 """

    def recursive_key_levels(a_dict, key_level=[]):
        """ y, 2017.8.14 """

        for key, value in a_dict.items():
            if type(value) is dict:
                yield key_level
                yield from recursive_key_levels(value, key_level + [key])
            else:
                yield key_level + [key]

    levels = [key_level for key_level in recursive_key_levels(a_dict) if len(key_level) > 0]
    return levels


def compare_dictionary_by_nested_keys(a_dict, b_dict):
    """ y, 2017.8.14

        return 1 if a_dict is superset of b_dict in key levels
        return 0 if a_dict is equal to b_dict in key levels
        return -1 if a_dict is subset of b_dict in key levels

    """

    a_set = set(map(str, get_listed_keys_in_a_nested_dictionary(a_dict)))
    b_set = set(map(str, get_listed_keys_in_a_nested_dictionary(b_dict)))

    return 1 if a_set > b_set else -1 if a_set < b_set else 0 if a_set == b_set else float('NaN')


a = {'a': {1: {2: 3, 4: 5}, 6: 7}, 8: {9: 0}}
b = {'a': {1: {2: 3,     }, 6: 7}, 8: {9: 0}}
c = {'a': {1: {2: 3,     }, 6: 7}, 8: {9: 0}, 0: 0}

print(compare_dictionary_by_nested_keys(a, a))
print(compare_dictionary_by_nested_keys(a, b))
print(compare_dictionary_by_nested_keys(b, a))
print(compare_dictionary_by_nested_keys(a, c))


