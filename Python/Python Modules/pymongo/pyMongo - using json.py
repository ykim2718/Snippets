"""
y, pyMongo - using json.py, 2017.6.20 - 22
"""

import sys
import pymongo
import json
import numpy as np
import inspect
import types
import pandas as pd
import datetime as dt


class MyObjectEncoder(json.JSONEncoder):
    """ y (copyRight)
        2016.5.15, 10.25 - 26, 11.10
        2017.3.18, 5.11, 6.6, 6.21
    """

    def default(self, obj):
        """ override super().default() """

        # 2017.5.11
        if isinstance(obj, type):
            return str(obj)
        # y, 2016.5.31, 10.26
        elif hasattr(obj, 'isoformat'):
            return obj.isoformat()
        # 2017.6.6
        elif isinstance(obj, (np.int_, np.intc, np.intp, np.int8, np.int16, np.int32, np.int64,
                              np.uint8, np.uint16, np.uint32, np.uint64)):
            return int(obj)
        # 2017.6.6
        elif isinstance(obj, (np.float_, np.float16, np.float32, np.float64)):
            return float(obj)
        # 2017.6.21
        # return string to avoid 'circular reference' error coming from builtin function in list or dict
        elif isinstance(obj, (types.BuiltinFunctionType, types.BuiltinMethodType)):
            return str(obj)
        # 2016.5.15 ~
        elif hasattr(obj, "__dict__"):
            a_dict = dict()
            obj_class_dict = dict(obj.__class__.__dict__)  # 2016.10.25
            obj_class_dict.update(obj.__dict__)  # 2017.3.18
            for key in obj_class_dict.keys():  # 2016.10.25, 2017.3.18
                value = getattr(obj, key)
                if any([key.startswith("__"),  # 2016.11.10, Because '__abstractmethods__' key brings crash.
                        inspect.isabstract(value),
                        inspect.isbuiltin(value),
                        inspect.isfunction(value),
                        inspect.isgenerator(value),
                        inspect.isgeneratorfunction(value),
                        inspect.ismethod(value),
                        inspect.ismethoddescriptor(value),
                        inspect.isroutine(value),
                        isinstance(value, pd.DataFrame),
                        isinstance(value, (types.BuiltinFunctionType, types.BuiltinMethodType)),
                        ],
                       ):
                    continue
                else:
                    a_dict[key] = value
            return self.default(a_dict)

        return obj


class MyObject:
    """ y, 2017.6.21 """

    def dump_to_dict(self):
        """ y, 2017.6.21 """

        jdumps = json.dumps(attributes, cls=MyObjectEncoder, indent=2, sort_keys=False, ensure_ascii=False)
        return json.loads(jdumps)

    def load_dict(self, a_dict):
        """ y, 2017.6.21 """

        for key, value in a_dict.items():
            setattr(self, key, value)

def function_outside():
    pass


class Glsss(MyObject):

    tricky = {1: print, 2: function_outside}
    time = dt.datetime.now()
    interger = 1
    float = 2.2
    tuple = (3,)
    list_ = {0, 'a', None, np.nan, '', [1, 2, 3]}
    dict_ = {'a': 1, 2: 3, 4: {5: 6, 7: 8,}}
    function = _print
    lambda_ = lambda x: print(x)

    def function(self):
        self.lambda_(self.a)


if __name__ == "__main__":

    g = Glass()
    doc = g.dump_to_dict()

    host = "pymongo://localhost"
    deposit = False

    db_server = pymongo.MongoClient(host, 27017)
    collection = db_server.terry.house

    withdraw = not depoist
    if deposit:  # write doc to MongoDB
        try:
            collection.insert(doc)
            print("succeeded in inserting")
        except:
            print("failed in inserting", sys.exc_info()[0])

    elif withdraw:  # read doc from MongoDB

        docs = collection.find({'integer': 1, 'float': 2.2})

        if docs.count() == 0:
            print('doc count =', 0)
            sys.exit(1)
        elif docs.count() > 1:
            print('doc count = ', docs.count())

        doc = docs[0]  # for simple demonstration
        doc_id = doc.pop('_id', None)  # prevent from 'circular reference' error during converting to json

        k = MyObject()
        k.load_dict(doc)
        print('widthdrawn .. \n', k.dump_to_dict())

    db_server.close()



