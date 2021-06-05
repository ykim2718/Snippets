"""
y, 2020.11.15
re - sub.py
https://greeksharifa.github.io/%EC%A0%95%EA%B7%9C%ED%91%9C%ED%98%84%EC%8B%9D(re)/2018/08/04/regex-usage-05-intermediate/
"""

import re

a = '1900-01-01'
b = re.sub('(\d{4})-(\d{2})-(\d{2})', r'\1.\2.\3', a)
print(b)

b = re.sub('(?P<year>\d{4})-(?P<month>\d{2})-(?P<day>\d{2})', '\g<year>.\g<month>.\g<day>', a)
print(b)
