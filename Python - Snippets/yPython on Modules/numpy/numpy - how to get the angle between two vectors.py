"""
y, 2020.4.16
numpy - how to get the angle between two vectors.py
https://kite.com/python/answers/how-to-get-the-angle-between-two-vectors-in-python
"""

import numpy as np

vector_1 = [-1, 0]
vector_2 = [1, 1]
print(f"vector_1={vector_1}")
print(f"vector_2={vector_2}")

unit_vector_1 = vector_1 / np.linalg.norm(vector_1)
unit_vector_2 = vector_2 / np.linalg.norm(vector_2)
print(f"unit_vector_1={unit_vector_1}")
print(f"unit_vector_2={unit_vector_2}")
dot_product = np.dot(unit_vector_1, unit_vector_2)
print(f"dot_product={dot_product}")

angle_in_radian = np.arccos(dot_product)
print(f"angle_in_radian={angle_in_radian}")
angle_in_degree = np.degrees(angle_in_radian)
print(f"angle_in_degree={angle_in_degree}")

"""
vector_1=[1, 0]
vector_2=[1, 1]
unit_vector_1=[1. 0.]
unit_vector_2=[0.70710678 0.70710678]
dot_product=0.7071067811865475
angle_in_radian=0.7853981633974484
angle_in_degree=45.00000000000001

vector_1=[0, 2]
vector_2=[1, 1]
unit_vector_1=[0. 1.]
unit_vector_2=[0.70710678 0.70710678]
dot_product=0.7071067811865475
angle_in_radian=0.7853981633974484
angle_in_degree=45.00000000000001

vector_1=[-1, 0]
vector_2=[1, 1]
unit_vector_1=[-1.  0.]
unit_vector_2=[0.70710678 0.70710678]
dot_product=-0.7071067811865475
angle_in_radian=2.356194490192345
angle_in_degree=135.0

vector_1=[0, -2]
vector_2=[1, 1]
unit_vector_1=[ 0. -1.]
unit_vector_2=[0.70710678 0.70710678]
dot_product=-0.7071067811865475
angle_in_radian=2.356194490192345
angle_in_degree=135.0
"""

