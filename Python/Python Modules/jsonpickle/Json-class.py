"""
y, 2016.5.15
http://stackoverflow.com/questions/3768895/how-to-make-a-class-json-serializable
"""
import json
import inspect


class ObjectEncoder(json.JSONEncoder):
    def default(self, obj):
        if hasattr(obj, "to_json"):
            return self.default(obj.to_json())
        elif hasattr(obj, "__dict__"):
            d = dict(
                (key, value)
                for key, value in inspect.getmembers(obj)
                if not key.startswith("__")
                and not inspect.isabstract(value)
                and not inspect.isbuiltin(value)
                and not inspect.isfunction(value)
                and not inspect.isgenerator(value)
                and not inspect.isgeneratorfunction(value)
                and not inspect.ismethod(value)
                and not inspect.ismethoddescriptor(value)
                and not inspect.isroutine(value)
            )
            return self.default(d)
        return obj


class C(object):
    c = "NO"

    def to_json(self):
        return {"c": "YES"}


class B(object):
    b = "B"
    i = "I"

    def __init__(self, y):
        self.y = y

    def f(self):
        print("f")


class A(B):
    a = "A"

    def __init__(self):
        self.b = [{"ab": B("y")}]
        self.c = C()


print(json.dumps(A(), cls=ObjectEncoder, indent=2, sort_keys=True))
