"""
y, pandas - find non-numeric rows.py, 2018.9.28
https://stackoverflow.com/questions/21771133/finding-non-numeric-rows-in-dataframe-in-pandas
https://stackoverflow.com/questions/354038/how-do-i-check-if-a-string-is-a-number-float
"""

import pandas as pd
import numpy as np

a = pd.Series(['hi', '+', '-', '.', '1.3e1', '-.1', '-0.21', '123'])
# a = a.str.replace('.', '')
# a = a.str.replace(',', '')
mask = a.str.isnumeric()
print(mask)


def is_number_string(x):
    """ y, 2018.9.28 """

    try:
        float(x)
        return True
    except:
        return False


mask = a.apply(lambda x: is_number_string(x))
print(mask.tolist())
