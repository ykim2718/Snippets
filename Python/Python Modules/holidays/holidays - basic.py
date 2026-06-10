"""
y, 2022.8.15
holidays - basic.py
https://pypi.org/project/holidays/
"""

from datetime import date
import holidays

if True:
    holidays = holidays.KOR(years=range(2021, 2022))
else:
    holidays = holidays.country_holidays('KOR')

print(holidays)
print(len(holidays))

