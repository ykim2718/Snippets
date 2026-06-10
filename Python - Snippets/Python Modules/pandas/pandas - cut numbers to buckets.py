"""
y, pandas - cut numbers to buckets.py, 2019.9.22
https://datascienceschool.net/view-notebook/aa62265f02fc429aa636ef343c3b1fda/  데이터프레임의 데이터 조작
"""


import pandas as pd

ages = [0, 2, 10, 21, 23, 37, 31, 61, 20, 41, 32, 100]
bins = [1, 15, 25, 35, 60, 99]
labels = ["미성년자", "청년", "중년", "장년", "노년"]
assert len(bins) == len(labels) + 1
cats = pd.cut(ages, bins, labels=labels)
print(type(cats))
print(cats)

df = pd.DataFrame(ages, columns=["ages"])
df["age_cat"] = pd.cut(df.ages, bins, labels=labels)
print(df)