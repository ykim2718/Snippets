"""
y, 2022.5.12
python list - nlargest.py
https://www.geeksforgeeks.org/python-program-to-find-n-largest-elements-from-a-list/
"""


def nlargest(a, n):
    largest = []
    for i in range(0, n):
        max1 = 0  # FIXME ???????
        for j in range(len(a)):
            if a[j] > max1:
                max1 = a[j];

        a.remove(max1);
        largest.append(max1)
    return largest


# Driver code
a = [2, 6, 41, 85, 0, 3, 7, 6, 10]
n = 2

# Calling the function
b = nlargest(a, n)
print(b)  # [85, 41]


import heapq

a = [2, 6, 41, 85, 0, 3, 7, 6, 10]
b = heapq.nlargest(n, a)
print(b)  # [85, 41]
