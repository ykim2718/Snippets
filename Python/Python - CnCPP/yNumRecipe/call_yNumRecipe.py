# -*- coding: utf-8 -*-
"""
Created on Sun Mar 26 22:57 2016 - Apr 2

@author: Y. Kim
"""

import yNumRecipe as y

y.demo_Fig_33_on_page_52()
y.demo_Fig_35_on_page_54()
y.demo_Fig_40_on_page_59()
for i in [1, 2, 3, 4, -1, -2, -3, -4]:
    y.demo_rectangle_9x9(i)

# demo_Fig_35_on_page_54()
xx = [-5.0, 5.0, 5.0, -5.0, -5.0, 0.0, 5.0, 0.0, -3.0, 3.0,
      +3.0, -3.0, -3.0, 0.0, 3.0, 0.0, -3.0, -3.0, -5.0]
yy = [-5.0, -5.0, 5.0, 5.0, 0.0, 5.0, 0.0, -5.0, -2.0, -2.0,
      +2.0, 2.0, 0.0, 2.0, 0.0, -2.0, 0.0, -2.0, 0.0]
n = len(xx)
area = y.new_doublePointer()
y.doublePointer_assign(area, 0)
ax = y.new_doubleArray(n)
ay = y.new_doubleArray(n)
for index, d_value in enumerate(xx, start=0):
    y.doubleArray_setitem(ax, index, d_value)
for index, d_value in enumerate(yy, start=0):
    y.doubleArray_setitem(ay, index, d_value)
prob = y.yBVSNCDFOCP(ax, ay, n, area)
print("yBVSNCDFOCP(demo_Fig_35_on_page_54) prob=", prob,
      "area=", y.doublePointer_value(area))
y.delete_doublePointer(area)
y.delete_doubleArray(ax)
y.delete_doubleArray(ay)

z = y.UVNParameter()
print("z=y.UVNParameter()", id(z))
z.mean = 0
z.stdev = 1
u = 1
print("yZscore1d(", u, "),n(", z.mean, ")", z.stdev, "^2))", y.yZscore1d(u, z))
z = y.BVNParameter()
print("z=y.BVNParameter()", id(z))
z.m_x = 1
z.s_x = 1
z.m_y = 2
z.s_y = 2
z.r = 0.999999999999
u = y.yZscore2d(1, 2, z)
print("u=", u)
# print("yZscore2d()",x,y.doublePointer_value(y))
