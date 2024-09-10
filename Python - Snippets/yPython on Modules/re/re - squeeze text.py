"""
y, 2024.9.9
re - squeeze.text.py
"""

import re

original_text = 'hhhh 【 8월 15대 주요 품목별 수출액(억달러) 및 증감률(%) 】tttt.... '
original_text = 'hhhh [ 8월 15대 주요 품목별 수출액(억달러) 및 증감률(%) ]tttt.... '
print(f"{original_text=}")
print(re.search(r"(\[.*?\])", original_text))
squeezed_text = re.sub(r"(\[.*?\])", lambda m: re.sub(r'\s+', ' ', m.group(1)), original_text)
print(f"{squeezed_text=}")

raise NotImplementedError('not working, 2024.9.9')