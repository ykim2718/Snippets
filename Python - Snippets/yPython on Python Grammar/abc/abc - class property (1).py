"""
y, 2025.10.5
abc - class property (1).py
"""

import abc


class PropertyEnforcingMeta(type):
    def __init__(cls, name, bases, namespace):
        super().__init__(name, bases, namespace)

        # Check for abstract property enforcement
        required_props = getattr(cls, '__required_properties__', [])
        for prop_name in required_props:
            attr = getattr(cls, prop_name, None)
            if not isinstance(attr, property):
                raise TypeError(f"{name} must implement '{prop_name}' as a property.")


# class Klass(metaclass=abc.ABCMeta):
class Klass(metaclass=PropertyEnforcingMeta):
    __required_properties__ = ['value']

    @property
    @abc.abstractmethod
    def value(self):
        pass


class Glass(Klass):

    @property
    def value(self):
        return 20251005


g = Glass()
print(f"{g.value=}")
