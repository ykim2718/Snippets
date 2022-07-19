import os
import sys
import math
import datetime as dt

count = int(float(sys.argv[1]))
start = dt.datetime.now()
print("%s at %s for %g, pid=%s" % (__file__, start, count, os.getpid()), sys.argv[1:])
r = math.factorial(count)
stop = dt.datetime.now()
running_time = stop - start
print("%s at %s (%s) for %g .. ended" % (__file__, stop, running_time, count))