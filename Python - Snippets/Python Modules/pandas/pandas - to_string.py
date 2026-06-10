"""
y, Pandas - to_string.py, 2018.2.15
"""

import pandas as pd

frame = pd.DataFrame([1, 2, 3, 4]).T
frame[0] = frame[0].astype(str)
frame[1] = frame[1].astype(int)
frame[2] = frame[2].astype(float)
frame[3] = frame[3].astype(float)
print(frame)
print(frame.dtypes)

print('\n')
outs = frame.to_string(float_format=str, header=None, index=None)
print(outs)

print('\n')
formatters = [
    str,
    lambda x: '{:g}'.format(x),
    lambda x: '(2)%.1f' % x,
    lambda x: '(3)%.1f' % x,
]
assert len(formatters) == len(frame.columns)
# float_format is not working because of 2nd priority to formatters
outs = frame.to_string(formatters=formatters, float_format=str)
print(outs)

print('\n')
formatters = {2: lambda x: '<2>%.1f' % x,
              3: lambda x: '<3>%.1f' % x,
              }
formatter = lambda x: '[%s]' % x
# float_format is working in parallel because of no specification to the first two columns
outs = frame.astype(float).to_string(formatters=formatters, float_format=formatter)
print(outs)
