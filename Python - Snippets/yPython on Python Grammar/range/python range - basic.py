"""
y, python range - basic.py, 2019.11.15
"""

start_0, stop_0 = 0, 3  # [0, 1, 2]
start_1, stop_1 = 4, 6  # [4, 5]

case = 'once'
if case == 'sliding_forward':
    ranges = zip(range(start_0, stop_0), range(start_1, stop_1))
elif case == 'sliding_backward':
    # ranges = reversed([*(zip(range(start_0, stop_0), range(start_1, stop_1))])
    ranges = reversed(list(zip(range(start_0, stop_0), range(start_1, stop_1))))  # TODO 2019.11.18, Need better
elif case == 'expanding_forward':
    ranges = zip([0] * (stop_1 - start_1 + 1), range(start_1, stop_1))
elif case == 'once':
    ranges = zip([stop_0], [stop_1])

print(case)
for j, k in ranges:
    print(j, k)

"""
sliding_forward
0 4
1 5

sliding_backward
1 5
0 4

expanding_forward
0 4
0 5

once
3 6
"""