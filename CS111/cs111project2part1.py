# -*- coding: utf-8 -*-
"""
Created on Fri Oct 11 17:31:06 2019

@author: tanuj
"""

def print_all_links(s):
    '''printing all the links in with href immediately after <a in given str '''
    y = 0
    if '<a' in s:
        while y < s.rfind('<a href'):
            x = s.find('<a href', y)
            r = s.find('>', x)
            y = s.find('"', x+10, r)
            e = s[x+9:y]
            print(e, end=' ')

webpage_source = input()
print_all_links(webpage_source)