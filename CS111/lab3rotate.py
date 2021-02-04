# -*- coding: utf-8 -*-
"""
Created on Wed Sep 11 20:42:51 2019

@author: tanuj
"""

alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'


def rotate(text, y):
    z = alphabet.find(text)
    a = y + z
    b = a % 26
    return alphabet[b]
