"""

y, Pandas - groupby.py, 2016.9.28, 2017.6.20

"""

import pandas as pd

print_ = lambda x: print('-' * 32, '\n', x, sep='')  # 2017.6.20

print_("y, 2016.9.28")
df = pd.DataFrame({'one': list('abracadabra')})
print(df)
j = df.groupby('one').size()
print(j, type(j))
k = j[['a', 'b']]
print(k, type(k))
l = k.sum()
print(l, type(l))

m = df.groupby('one').size()[['a', 'b']].sum()
print('all in one =', m)

chk = (list(df['one'] == 'a') + list(df['one'] == 'b')).count(True)
print('check =', chk)

