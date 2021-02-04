# -*- coding: utf-8 -*-
"""
Created on Wed Sep 25 10:27:30 2019

@author: tanuj
"""

alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
vigenere = {}

def cencrypt(x, y):
    c = ''
    x = x.upper()
    for a in x:
        if a in alphabets:
            a = alphabets[(alphabets.find(a) + y)%len(alphabets)]
            c = c + a
    return c

def c_encrypt(x, y):
    c = ''
    x = x.upper()
    a = cencrypt(x, y)
    c = c + a
    return c

def c_decrypt(x, y):
    c = ''
    x = x.upper()
    a = cencrypt(x, -y)
    c = c + a
    return c
    
def vig_encrypt(x, y):
    c = ''
    x = x.upper()
    y = y.upper()
    b = 0
    for a in x:
        alpha = x[b%len(x)]
        g = y[b%len(y)]
        pos = alphabets.find(g)
        e = cencrypt(alpha , pos)
        c = c + e
        b = b + 1
    return c

def vig_decrypt(x, y):
    c = ''
    x = x.upper()
    y = y.upper()
    b = 0
    for a in x:
        alpha = x[b%len(x)]
        g = y[b%len(y)]
        pos = alphabets.find(g)
        e = cencrypt(alpha , -pos)
        c = c + e
        b = b + 1
    return c
                
                
                
                
            
            
            
            
            
            
            
            
            
            
            
            