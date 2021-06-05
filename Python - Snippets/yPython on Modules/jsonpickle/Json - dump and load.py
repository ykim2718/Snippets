"""
y, Json - dump and load.py, 2015.5.15 - 5.30
"""

import io
import os
import json
import inspect


class ObjectEncoder(json.JSONEncoder):
    """
    y (copyRight) 2016.5.15
    http://stackoverflow.com/questions/3768895/how-to-make-a-class-json-serializable
    """

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
        # y, 2016.5.31
        # http://stackoverflow.com/questions/23285558/datetime-date2014-4-25-is-not-json-serializable-in-django
        elif hasattr(obj, 'isoformat'):
            return obj.isoformat()
        return obj


class YMyClass(object):
    code = None
    local_start_date = '2000-1-1'
    local_stop_date = '2015-12-31'
    line_count = 0
    query_db_start_date = None
    query_db_stop_date = None
    remote_db_start_date = None
    remote_db_stop_date = None
    update_count = 0
    update_date = None

    json_dt_formats = {
        '10': '%Y-%m-%d',
        '19': '%Y-%m-%dT%H:%M:%S',
        'else': '%Y-%m-%dT%H:%M:%S.%f'
    }

    def json_dt_format(self, date_time):
        return self.json_dt_formats.get(
            str(len(date_time)), self.json_dt_formats['else'])

    def write_json(self, file=None):
        if file is None:
            return
        with io.open(file, 'w', encoding='utf-8') as f:
            jdumps = json.dumps(self,
                                cls=ObjectEncoder, indent=2, sort_keys=True, ensure_ascii=False)
            f.write(jdumps)
        return

    def read_json(self, file=None):
        if file is None:
            return
        if os.path.isfile(file) is False or os.path.getsize(file) == 0:
            return
        with io.open(file, 'r', encoding='utf-8') as f:
            self.__dict__ = json.load(f)
        self.local_start_date = dt.datetime.strptime(
            self.local_start_date, self.json_dt_format(self.local_start_date))
        self.local_stop_date = dt.datetime.strptime(
            self.local_stop_date, self.json_dt_format(self.local_stop_date))


if __name__ == '__main__':
    file = __file__[:-3] + '.json'

    import datetime as dt

    myc = YMyClass()
    myc.code = '12345'
    myc.local_start_date = dt.datetime(2016, 5, 30, 18, 33, 0)
    myc.local_stop_date = dt.date(2016, 5, 31)
    myc.update_date = dt.datetime.now()
    myc.write_json(file)
    myc.read_json(file)

    print(myc.local_start_date, type(myc.local_start_date))
    print(myc.local_stop_date, type(myc.local_stop_date))
    print(myc.update_date, type(myc.update_date))
