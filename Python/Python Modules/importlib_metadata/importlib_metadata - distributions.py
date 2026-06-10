"""
y, 2024.6.10
importlib_metadata - distributions.py
ChatGPT3.5
"""

import importlib.metadata

for dist in importlib.metadata.distributions():
    print(f"{dist.name=}: {dist.version=}")
