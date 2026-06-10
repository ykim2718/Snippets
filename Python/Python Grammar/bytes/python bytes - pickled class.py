"""
y, python bytes - pickled class.py, 2019.4.9
https://docs.python.org/3/library/stdtypes.html
"""

import pickle


class Klass:

    one = 1

    def two(self):

        return 2


glass = Klass()
pickled = pickle.dumps(glass)
hexlified = bytes(pickled).hex()
print(hexlified, type(hexlified))
unhexlified = bytes.fromhex(hexlified)
unpickled = pickle.loads(unhexlified)
print(type(unpickled))
print(unpickled.one)
print(unpickled.two())