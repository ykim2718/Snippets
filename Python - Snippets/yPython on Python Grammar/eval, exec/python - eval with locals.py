"""
y, python - eval with locals.py, 2018.5.1, 10.3
https://stackoverflow.com/questions/29695794/typeerror-iter-takes-no-keyword-arguments?rq=1  << known-bug
"""

a = 1
b = eval('a + 1', locals())
print(a, b)
b = eval('a + 1', {'a': 3})
print(a, b)
b = eval('a + 1', None)
print(a, b)
