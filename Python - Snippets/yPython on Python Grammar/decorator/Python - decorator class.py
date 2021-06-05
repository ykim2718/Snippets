"""
y, Python - decorator class.py, 2016.6.11, 2017.12.4
https://andrefsp.wordpress.com/2012/08/23/writing-a-class-decorator-in-python/
"""

def class_decorator(*method_names):

    def method_decorator(fn):
        # Example of a method decorator
        def decorator(*args, **kwargs):
            print("\tInside the decorator")
            return fn(*args, **kwargs)

        return decorator

    def class_rebuilder(AClass):  # argument here takes class object !!!
        # The class decorator example
        print(type(AClass), AClass.a)

        class NewClass(AClass):
            # This is the overwritten class
            def __getattribute__(self, attr_name):
                obj = super(NewClass, self).__getattribute__(attr_name)
                if hasattr(obj, '__call__') and attr_name in method_names:
                    return method_decorator(obj)
                return obj

        return NewClass

    return class_rebuilder


@class_decorator('first_method', 'second_method')
class MySecondClass(object):
    a = 'MySecondClass'
    b = 2

    def first_method(self, *args, **kwargs):
        print("\t\tthis is the MySecondClass.first_method")

    def second_method(self, *args, **kwargs):
        print("\t\tthis is the MySecondClass.second_method")


if __name__ == "__main__":
    print("::: With a decorated class :::")
    z = MySecondClass()
    z.first_method()
    z.second_method()
    print(z.a, z.b)
