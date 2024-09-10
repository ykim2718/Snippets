"""
y, 2024.9.9 - 10
re - squeeze.text.py
"""

import re

original_text = 'hhhh 【 8월 15대 주요 품목별 수출액(억달러) 및 증감률(%) 】tttt.... '
original_text = 'hhhh [ 8월 15대 주요 품목별 수출액(억달러) 및 증감률(%) ]tttt.... '
print(f"{original_text=}")
r = re.search(r"(\[.*?\])", original_text)
print(f"{r.group(1)=}")
squeezed_text = re.sub(r"(\[.*?\])", lambda m: re.sub(r'\s+', '', m.group(1)), original_text)
print(f"{squeezed_text=}")