"""
y, 2022.11.5
python - slash in arguments.py
https://stackoverflow.com/questions/24735311/what-does-the-slash-mean-in-help-output
"""


def foo(a, b, /, x, y):
    print("positional", a, b, "|", "positional or keyword", x, y)


foo(1, 2, 3, 4)
foo(1, 2, 3, y=4)
foo(1, 2, x=3, y=4)

# foo(a=1, b=2, x=3, y=4) # TypeError: foo() got some positional-only arguments passed as keyword arguments: 'a, b'


def zoo(a, b, /, x, *, y):
    print("positional", a, b, "|", "positional or keyword", x, y)


# zoo(1, 2, 3, 4)  # TypeError: zoo() takes 3 positional arguments but 4 were given
zoo(1, 2, 3, y=4)
zoo(1, 2, x=3, y=4)
# zoo(1, b=2, x=3, y=4) # TypeError: zoo() got some positional-only arguments passed as keyword arguments: 'b'
