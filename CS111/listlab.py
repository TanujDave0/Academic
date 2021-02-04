# -*- coding: utf-8 -*-
"""
Created on Wed Oct  2 19:39:22 2019

@author: tanuj
"""

def list4(a,b,c,d):
    """defining list4 to find max of a b c d if  int or float"""
    list1 = [a,b,c,d]
    if ((type(a) == int) or (type(a)==float)) and ((type(b) == int) or (type(b)==float)) and ((type(c) == int) or (type(c)==float)) and ((type(d) == int) or (type(d)==float)): #creating if statement to detect if all elements are int or float
        e = max(list1)
    else:
        e = list1
    return e #getting output