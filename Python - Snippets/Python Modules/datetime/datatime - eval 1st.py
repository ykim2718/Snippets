"""
y, 2016.4.23
"""


def GetBusinessDayCount(start, end):
    import numpy as np
    import datetime as dt

    y, m, d = start.split('-')
    start = dt.date(int(y), int(m), int(d))
    y, m, d = end.split('-')
    end = dt.date(int(y), int(m), int(d))
    days = np.busday_count(start, end)

    return days


def GetDatePeriodExtension(start, end, certain_date):
    """
    Y (copyRigth) 2016.4.21 - 23
    :param start: date string in the form of 'YYYY-MM-DD'
    :param end: date string in the form of 'YYYY-MM-DD'
    :param certain_date: date string in the form of 'YYYY-MM-DD'
    :return: [new start,end]
    """
    import time
    import datetime as dt

    format = "%Y-%m-%d"
    start = time.strptime(start, format)
    end = time.strptime(end, format)
    certain_date = time.strptime(certain_date, format)

    if certain_date < start:
        certain_date = time.strftime(format, certain_date)
        t = start
        start = dt.date(t.tm_year, t.tm_mon, t.tm_mday) + dt.timedelta(-1)
        start = start.strftime(format)
        return [certain_date, start]
    elif end < certain_date:
        t = end
        end = dt.date(t.tm_year, t.tm_mon, t.tm_mday) + dt.timedelta(1)
        end = end.strftime(format)
        certain_date = time.strftime(format, certain_date)
        return [end, certain_date]
    else:
        return None


def GetDateLaterThanDateRef(date_ref, byHowManyDates):
    """
    y (copyRight) 2016.4.24
    :param date_ref: date string in the form of 'YYYY-MM-DD'
    :param byHowManyDates: date count -> <0 for earlier, >0 for later
    :return: date from the date reference in the form of 'YYYY-MM-DD'
    """

    import time
    import datetime as dt

    format = "%Y-%m-%d"
    t = time.strptime(date_ref, format)
    date_new = dt.date(t.tm_year, t.tm_mon, t.tm_mday) + dt.timedelta(byHowManyDates)
    date_new = date_new.strftime(format)

    return date_new


if __name__ == "__main__":
    import datetime as dt

    today = dt.date.today()
    print(today)

    print('\ny, 2016.4.23, GetBusinessDayCount()')
    r = GetBusinessDayCount('2016-4-23', '2016-4-25')
    print(r)

    print('\ny, 2016.4.24, GetDatePeriodExtension()')
    r = GetDatePeriodExtension('2010-1-1', '2015-4-30', '2016-2-5')
    print(r)

    print('\ny, 2016.4.24, GetDatePeriodExtension()')
    r = GetDateLaterThanDateRef('2016-1-1', -30)
    print(r)
