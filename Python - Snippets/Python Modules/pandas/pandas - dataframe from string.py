"""
y, 2020.7.1
pandas - dataframe from string.py
https://kite.com/python/answers/
"""

import io
import pandas as pd


data_string = """Letters, Numbers
                 a, 1
                 b, 2
                 c, 3"""
data_string = "Letters, Numbers\na, 1\nb, 2\nc, 3"
print(data_string)

data = io.StringIO(data_string)
frame = pd.read_csv(data, sep=",")
print(frame)