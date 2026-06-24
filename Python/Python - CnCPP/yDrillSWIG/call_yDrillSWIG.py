import yDrillSWIG as y
import numpy

r = y.new_intPointer()
y.intPointer_assign(r, 99)
a = y.new_intArray(8)
for i in [1, 2, 3, 4, 5, 6, 7, 8]:
    y.intArray_setitem(a, i, i)
y.check_array1d(a, 8, r)
print("(yPython) result=", y.intPointer_value(r))
y.delete_intPointer(r)
y.delete_intArray(a)

a2d = numpy.array([[1, 2, 3], [4, 5, 6]])
print(a2d)
y.check_array2d_w_numpy(a2d)
print(a2d)
