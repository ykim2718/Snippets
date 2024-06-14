"""
y, 2024.6.10
importlib_metadata - DistributionFinder.py
"""


import importlib_metadata

ctx = importlib_metadata.DistributionFinder.Context()
for path in ctx.path:
    print(f"{path=}")

"""
path='D:\\Wolf-Code\\yStudy_on_code_-_Python\\Python - Snippets\\yPython on Modules\\importlib_metadata'
path='D:\\Wolf-Code\\yStudy_on_code_-_Python'
path='D:\\Wolf-Code\\yStudy_on_code_-_Python\\Python - Y'
path='C:\\Y\\anaconda3\\python310.zip'
path='C:\\Y\\anaconda3\\DLLs'
path='C:\\Y\\anaconda3\\lib'
path='C:\\Y\\anaconda3'
path='C:\\Y\\anaconda3\\lib\\site-packages'
path='C:\\Y\\anaconda3\\lib\\site-packages\\win32'
path='C:\\Y\\anaconda3\\lib\\site-packages\\win32\\lib'
path='C:\\Y\\anaconda3\\lib\\site-packages\\Pythonwin'
"""