# -*- coding: utf-8 -*-
"""
Created on Wed Sep 18 10:28:41 2019

@author: tanuj
"""

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

dict = {}

def cencrypt(x, y):
    a = ''
    x = x.upper()
    for c in x:
        if c in alphabet:
            d = alphabet[(alphabet.find(c) + y) % 26]
            a = a + d
    return a

    