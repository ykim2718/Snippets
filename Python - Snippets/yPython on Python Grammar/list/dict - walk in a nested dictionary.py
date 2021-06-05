"""
y, dict - get_dict_of_dotted_key_in_a_nested_dictionary(), 2017.7.14

"""

def get_dict_of_dotted_key_in_a_nested_dictionary(dict, key):

    head, _, tail = key.partition('.')
    if bool(tail):
        return get_dict_of_dotted_key_in_a_nested_dictionary(dict[head], tail)
    else:
        return dict, key

my_dict = {'first': {'second': {'third': 3, '3rd': 4}, '2nd': 2}}
d, k = get_dict_of_dotted_key_in_a_nested_dictionary(my_dict, "first.second.third")
print(d, k, d[k])

d[k] = 999
print(my_dict)