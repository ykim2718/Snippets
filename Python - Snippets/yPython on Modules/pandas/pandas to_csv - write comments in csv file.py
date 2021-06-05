"""
y, pandas to_csv - write comments in csv file.py, 2018.9.14
https://stackoverflow.com/questions/29233496/write-comments-in-csv-file-with-pandas
"""

import pandas as pd

frame = pd.DataFrame({'A': [1, 2], 'B': [3, 4]}, index=list('ab'))
print(frame)

_file_name = 'test.csv'

if False:
    f = open(_file_name, 'a')
    f.write('Comments here ...\n')
    frame.to_csv(f)
    f.close()
else:
    with open(_file_name, 'w') as f:
        f.write('Comments here ...\n')
        f.write(str({1: 2, 3: 4}) + '\n')
    frame.to_csv(_file_name, mode='a')
