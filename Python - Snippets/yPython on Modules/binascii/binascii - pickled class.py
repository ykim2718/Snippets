"""
y, binascii - pickled class.py, 2019.4.9
https://docs.python.org/3/library/binascii.html
"""

import binascii
import pickle


class Klass:

    one = 1

    def two(self):

        return 2


glass = Klass()
pickled = pickle.dumps(glass)
hexlified = binascii.hexlify(pickled)
print(hexlified, type(hexlified))
unhexlified = binascii.unhexlify(hexlified)
unpickled = pickle.loads(unhexlified)
print(type(unpickled))
print(unpickled.one)
print(unpickled.two())

