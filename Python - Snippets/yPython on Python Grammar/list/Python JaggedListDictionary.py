"""
Yongshik Kim (copyRight) 2014.4.4
"""

# knob dictionary composed of jagged list whose each element has
# step, recipe and more
k = {'knob': [['step', 'recipe']]}
k['k1'] = [['step1', 'recipe1']]
k['k2'] = [['s22', 'r22'], ['s23', 'r23']]
k['k1'].append(['s11', 'r11'])
k['k1'].append(['s12', 'r12'])


def print_dictionary(dic):
    for key, value in dic.items():
        for val in value:
            print(' ' * 2, key, 'has', val)


print("Python dictionary =", k)
print_dictionary(k)

import pandas

df = pandas.DataFrame([k])
# print("Pandas DataFrame =",df)
k = df.to_dict('list')
for key, value in k.items(): k[key] = value[0]
print("Pandas DataFrame to Dictionary =", k)
print_dictionary(k)
