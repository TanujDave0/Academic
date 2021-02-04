# -*- coding: utf-8 -*-
"""
Created on Wed Oct  2 20:31:26 2019

@author: tanuj
"""
def make_triangle(x,y):
    """creating fxn to make a isosceles triangle of x char with y times 'x' char in last line """
    b = 1
    c = ''
    d = ''
    for dig in range(y):
        if b <= y:
            c += x + ' ' 
            b += 1
        d += c + '\n'
    return d