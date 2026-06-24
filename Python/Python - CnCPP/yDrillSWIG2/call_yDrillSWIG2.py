# Passing Python array to c++ function with SWIG
# http://stackoverflow.com/questions/5251042/passing-python-array-to-c-function-with-swig

import yDrillSWIG2 as y

a = y.Array()
a = [[0, 1], [2, 3]]
y.print_array(a)
