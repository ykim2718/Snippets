"""
y, 2020.4.15
uuid - basic,py
https://stackoverflow.com/questions/3530294/how-to-generate-unique-64-bits-integers-from-python
"""

import uuid

url = 'https://www.naver.com/'
print(uuid.uuid1())
print(uuid.uuid3(uuid.NAMESPACE_URL, url))
print(uuid.uuid4())
print(uuid.uuid5(uuid.NAMESPACE_URL, url))
print(uuid.uuid1().int >> 64)