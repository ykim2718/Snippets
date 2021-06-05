"""
y, 2017.7.31

https://www.blog.pythonlibrary.org/2016/03/01/python-101-all-about-imports/

"""

import sys
import my_module

print(sys.modules)
print(my_module)
print(dir(my_module))

my_module.module.print_it()
my_module.module1.module1.print_it()
my_module.module2.module2.print_it()

