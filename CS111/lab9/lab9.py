# -*- coding: utf-8 -*-
"""
Created on Sat Dec  7 02:23:47 2019

@author: tanuj
"""

def prod(a,b):
    '''gives product of inergers from 'a' to 'b' inclusive '''
    for num in range(a+1,b+1):
        a*=num
    return a

def word_count(s):
    '''gives number of words in 's' '''
    a = len(s.split())
    return a

def wc(z):
    '''gives number of lines, number of words and number of characters in file 'z' '''
    r = open(z, 'r')
    s = r.read()
    a=1
    b=0
    for char in s:
        if char == '\n':
            a+=1
        b+=1
    c = word_count(s)
    if s[-1] == '\n':
        print(a-1,'\t' , c,'\t' , b)
    else:
        print(a,'\t' , c,'\t' , b)