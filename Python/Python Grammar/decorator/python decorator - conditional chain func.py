"""
y, python decorator - conditional chain func.py, 2019.4.20
"""

import functools


def conditional_chain_class_method(condition='_chain_reaction_flag'):
    """
    y,  2017.12.4
        2019.4.20

    Purpose
    -------
    . Make class method able to be used in a chain method, like a.plan().do().see().check()
    """

    def wrapper(f):
        @functools.wraps(f)
        def wrapped(self, *args, **kwargs):
            if not hasattr(self, condition):
                setattr(self, condition, True)
            if getattr(self, condition):
                result = f(self, *args, **kwargs)
                assert result is None
            return self
        return wrapped
    return wrapper


class Klass:

    @conditional_chain_class_method()
    def A(self):
        print('a')

    @conditional_chain_class_method()
    def B(self):
        print('b')
        self._chain_reaction_flag = False

    @conditional_chain_class_method()
    def C(self):
        print('C')


glass = Klass()
glass.A().B().C()


