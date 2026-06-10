# y, 2016.4.16
class SMTP:
    def lookupMethod(self, command):
        return getattr(self, 'do_' + command.upper(), None)

    def do_HELO(self, rest):
        return 'Howdy ' + rest

    def do_QUIT(self, rest):
        return 'Bye'


r = SMTP().lookupMethod('HELO')('foo.bar.com')  # => 'Howdy foo.bar.com'
print(r)
r = SMTP().lookupMethod('QUIT')('')  # => 'Bye'
print(r)

# y, 2016.4.16
choices = {'a': 1, 'b': 2}
r = choices.get('c', 'default')
print(r)

# y, 2016.4.21
# http://stackoverflow.com/questions/60208/replacements-for-switch-statement-in-python
v = 'a'
x = 2
r = {
    'a': lambda x: x * 5,
    'b': lambda x: x + 7,
    'c': lambda x: x - 2
}[v](x)
print(r)

# y, 2016.4.16
"""
func, args = {
  'a' : (obj.increment, (x,)),   # x++ in c
  'b' : (obj.decrement, (x,)),   # x-- in c
}.get(value, (obj.default, (x,)))
r = func(*args)
print(r)
"""
