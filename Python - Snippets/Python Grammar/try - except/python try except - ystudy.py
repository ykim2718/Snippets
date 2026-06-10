"""
y, python try except - ystudy.py
2016.4.16,
2017.9.9
"""

try:
    # raise ValueError("value error message here")
    # a = 1 / 0
    # raise RuntimeError("runtime error message here")
    raise Exception("exception message here")
except RuntimeError as ex:
    print('>>> RuntimeError <<<', type(ex).__name__, ex.args)
except ValueError as ex:
    print('>>> ValueError <<<', type(ex).__name__, ex.args)
except Exception as ex:
    print('>>> Exception <<<')
    print("[{0}] {1!r}".format(type(ex).__name__, ex.args), str(ex))
else:
    print('>>> else <<<')
finally:
    print('>>> finally <<<')
