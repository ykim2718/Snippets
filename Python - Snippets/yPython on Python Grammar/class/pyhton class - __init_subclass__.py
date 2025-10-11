"""
y, 2025.10.11
python class - __init_subclass__.py
"""


class Parent:
    setting = 'default'

    # @classmethod
    def __init_subclass__(cls, **kwargs):
        super().__init_subclass__(**kwargs)

        # Check if 'setting' is overridden in the child class
        if 'setting' in cls.__dict__:
            print(f"{cls.__name__} overrides 'setting'")
        else:
            print(f"{cls.__name__} inherits 'setting' from Parent")


class Child(Parent):
    setting = 'custom'  # Overrides


class Inherited(Parent):
    pass  # Inherits
