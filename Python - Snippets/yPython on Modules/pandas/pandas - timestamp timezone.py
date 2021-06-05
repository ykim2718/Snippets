"""
y, 2020.1.28
pandas - timestamp timezone.py
https://rfriend.tistory.com/505
https://gist.github.com/heyalexej/8bf688fd67d7199be4a1682b3eec7568
"""

import pandas as pd


now = pd.Timestamp.now(tz='Asia/Seoul')
print(now)
print(now.tz_convert(tz='Asia/Seoul').tz_convert(tz='Asia/Seoul'))  # no change if time zone is identical.
print(now.tz_convert('Europe/London'))
print(now.tz_convert(None))  # just take the time zone off.
