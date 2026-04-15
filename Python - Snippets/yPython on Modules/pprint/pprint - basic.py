"""
y, 2021.5.2; 2026.4.15
pprint - basic.py
"""

import pprint
from copy import deepcopy

d = {
    'a': 1,
    'b': dict(a=2, b=3),
    'c': [f"abc_{j}" for j in range(33)]
}
d['d'] = deepcopy(d)
p = pprint.pformat(d, indent=2, width=80, compact=True)
print(p)
print(f"{type(p)=}")

# pprint로 출력된 결과물은 json.loads로 직접 읽을 수 없습니다.
# 만약 pprint로 출력된 (파이썬 형태의) 문자열을 다시 파이썬 객체로 변환하고 싶다면 json.loads 대신 **ast.literal_eval**을 사용해야 합니다.