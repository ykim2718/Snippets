"""
y, python - exec with locals.py, 2018.4.23
https://stackoverflow.com/questions/1463306/how-does-exec-work-with-locals
"""

def foo():
    ldict = locals()
    exec("a=3",globals(),ldict)
    a = ldict['a']
    print(a)

foo()