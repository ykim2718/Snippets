"""
y, python grammar - for zip range.py, 2018.12.3
"""

X = [1, 2, 3, 4, 5]
Y = [10, 20]
start_x, start_y = 3, 0
step_x, step_y = 2, 1
batch_size_x, batch_size_y = 2, 1

stop_x, stop_y = len(X)-batch_size_x+1, len(Y)-batch_size_y+1
for j, k in zip(range(start_x, stop_x, step_x), range(start_y, stop_y, step_y)):
    x_index = list(range(j, j + batch_size_x, 1))
    y_index = list(range(k, k + batch_size_y, 1))
    print('x=', x_index, 'y=', y_index)

count = min(len(range(start_x, stop_x, step_x)), len(range(start_y, stop_y, step_y)))
print('count=%d' % count)
