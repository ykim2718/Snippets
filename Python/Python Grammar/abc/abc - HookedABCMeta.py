"""
y, 2025.10.5
abc - HookedABCMeta.py
"""

import abc


def on_subclass_validated(cls):
    print(f"Validated subclass: {cls.__name__}")
    # Add logging, registration, enforcement, etc.


class HookedABCMeta(abc.ABCMeta):
    def __init__(cls, name, bases, namespace):
        super().__init__(name, bases, namespace)
        # print(f"{name=}, {bases=}, {cls.__abstractmethods__=}")
        if bases:
            for name in cls.__abstractmethods__:
                attr = cls.__dict__.get(name)
                if isinstance(attr, property):
                    print(f"\t{name} is an abstract property")
                elif isinstance(attr, classmethod):
                    print(f"\t{name} is an abstract classmethod")
                elif isinstance(attr, staticmethod):
                    print(f"\t{name} is an abstract staticmethod")
                else:
                    print(f"\t{name} is an abstract method")
            else:
            # if not cls.__abstractmethods__:
                on_subclass_validated(cls)


class Base(metaclass=HookedABCMeta):
    @abc.abstractmethod
    def run(self):
        pass

    @property
    @abc.abstractmethod
    def value(self):
        pass


class Child(Base):
    def run(self):
        pass

    def value(self):
        return 1


# t = Child()
