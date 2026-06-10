"""
y, Pandas - dataframe read_csv.py, 2017.9.1

"""

import pandas as pd
a_dict = {
    'a': {
        1: 2,
        3: 4,
        5: 6
    },
    'b': {
        1: 20,
        3: 40,
        5: 60
    }
}

df = pd.DataFrame.from_dict(a_dict, orient='index')
print(df)