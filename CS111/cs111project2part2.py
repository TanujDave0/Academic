# -*- coding: utf-8 -*-
"""
Created on Sun Oct 13 16:03:34 2019

@author: tanuj
"""

def list_all_lnks(s):
    '''printing all the links in with href immediately after <a in given str'''
    y = 0
    list = []
    if '<a' in s:
        while y < s.rfind('<a href'):
            x = s.find('<a href', y)
            r = s.find('>', x)
            y = s.find('"', x+10, r)
            list.append(s[x+9:y])
    return list
