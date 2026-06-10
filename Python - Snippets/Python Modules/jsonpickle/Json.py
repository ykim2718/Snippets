"""
y, 2016.5.15
"""

import json

alist = [1, 2, 3]
adict = {'a': 11, 'b': 22, 'c': None, 'd': {'d-1': [1, 2, 3], 'd-2': True}}

print(adict['d']['d-2'])

json_str = json.dumps(adict)
print(json_str)
data = json.loads(json_str)

file = __file__[:-3] + '.json'

with open(file, 'w') as f:
    json.dump(data, f)

with open(file, 'r') as f:
    data = json.load(f)

print(data)
