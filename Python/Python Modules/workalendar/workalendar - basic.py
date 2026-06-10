"""
y, workalendar - basic.py, 2019.3.12
https://github.com/peopledoc/workalendar
"""

from datetime import date
from workalendar.europe import France
cal = France()
holidays = cal.holidays(2012)
print(holidays, len(holidays))

from workalendar.asia import SouthKorea
cal = SouthKorea()
holidays = cal.holidays(2019)
print(holidays, len(holidays))
