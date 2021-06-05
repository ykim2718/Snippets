"""
y, 2016.4.21
http://stackoverflow.com/questions/8142364/how-to-compare-two-dates
"""

import time


def demo():
    date1 = "31/12/2015"
    date2 = "01/01/2016"

    newdate1 = time.strptime(date1, "%d/%m/%Y")
    newdate2 = time.strptime(date2, "%d/%m/%Y")

    if newdate1 < newdate2:
        print("%s is earlier than %s" % (date1, date2))
    else:
        print("%s is later than %s" % (date1, date2))


if __name__ == "__main__":
    demo()
