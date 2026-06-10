"""
y, 2016.4.1 - 9.11, re - basic eval.py
https://docs.python.org/3.2/library/re.html
http://www.tutorialspoint.com/python/python_reg_expressions.htm
"""
import re

line = "Cats are smarter than dogs";

matchObj = re.match(r'dogs', line, re.M | re.I)
if matchObj:
    print("match --> matchObj.group() : ", matchObj.group())
else:
    print("No match!!")

searchObj = re.search(r'dogs', line, re.M | re.I)
if searchObj:
    print("search --> searchObj.group() : ", searchObj.group())
else:
    print("Nothing found!!")

line = "Adjusted Close"
if re.match(r'Adj*\w* Close', line, re.I):
    print("Matched")
else:
    print("No match !!")

replacements = {
    'first': 'bunch of ',
    'blow': 'bumbs',
    '{': '(',
    '}': ')',
}

expr = " The tree is {not} felled by the first blow."
pattern = '|'.join(re.escape(key) for key in replacements.keys())
expr = re.sub(
    '|'.join(re.escape(key) for key in replacements.keys()),
    lambda key: replacements[key.group(0)],
    expr).strip()
print(expr)

print()
print('y, 2016.4.18')
date = '2016-4-8'
if re.match('\d\d\d\d-\d?\d-\d?\d', date):
    print("%s matched" % date)
else:
    print("%s not matched" % date)
date = '2016-0408'
if re.match('\d{8}', date):
    print("%s matched" % date)
else:
    print("%s not matched" % date)

print()
print('y, 2016.4.22')
date = '2016-4-22 00:00:00'
date = '2016-4-22   '
date = '16-4-22'
if re.match('\d*-\d?\d-\d?\d$', date):
    print("%s matched" % date)
else:
    print("%s not matched" % date)

print()
print('y, 2016.4.28')
s = "A\nBoo"
print(s, re.match("A\s*B", s))  # matched
s = "oooA\nBooo"
print(s, re.match(".*A\s*(?!C).", s))  # matched
s = "o\n(A\B)"
print(s, re.match(".*\s*\(A\\\\B\)", s))  # matched
print(s, re.match("AB", "C"))

print()
print('y, 2016.5.20l, string replacement using re.sub')
# pattern = re.compile('b(?!b)')
pattern = re.compile('b')
print(pattern.search('abbc'))
print(re.sub('b', 'x', 'abbc'))
print(re.sub('b+', 'x', 'abbc'))

print()
print('y, 2016.5.20, A simple way to remove multiple spaces in a string in Python')
s = 'The    fox jumped   over   the  log.'
print(re.sub('\s+', ' ', s))

print()
print('y, 2016.9.11, *(??)*')
s = " a (22)"
print(s, re.match(".*\(\w\w\)$", s))


