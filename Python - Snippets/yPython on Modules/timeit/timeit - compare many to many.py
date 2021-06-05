"""
y, timeit - compare many to many.py, 2018.2.23
"""

import re
import timeit

strings = ['string%d' % j for j in range(9)]
patterns = strings.copy()

run_time = timeit.timeit("""
matched = [string for string in strings if any([re.match(pattern, string) for pattern in patterns])]
""", globals=globals(), number=int(1e4))
print(run_time)

run_time = timeit.timeit("""
matched = set(strings)
for pattern in patterns:
    k = len(strings)
    for j in range(k):
        if re.match(pattern, strings[j]):
            strings.pop(j)
            break
matched -= set(strings)
# print(matched)
""", globals=globals(), number=int(1e4))
print(run_time, "<<< best")

strings = ['string%d' % j for j in range(9)]
run_time = timeit.timeit("""
matched = []
for pattern in patterns:
    for string in strings:
        if re.match(pattern, string):
            matched.append(string)
            break
# print(matched)
""", globals=globals(), number=int(1e4))
print(run_time)
