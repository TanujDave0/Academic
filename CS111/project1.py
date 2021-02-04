# -*- coding: utf-8 -*-
"""
Created on Wed Sep 25 10:27:30 2019

@author: tanuj
"""

alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

def cencrypt(x, y):
    """Determining a function that takes two inputs and rotates x by y """
    c = ''
    x = x.upper()
    for a in x:
        if a in alphabets:
            a = alphabets[(alphabets.find(a) + y)%len(alphabets)]
            c = c + a
        else:
            c = c + a
    return c#returning desired output

def c_encrypt(x, y):
    """Ceasar encrypt function, rotates x by y using cencrypt function """
    c = ''
    x = x.upper()
    a = cencrypt(x, y) #calling cencrypt function
    c = c + a
    return c #returning desired output

def c_decrypt(x, y):
    """Ceasar decrypt function, rotate x by -y, or decrypts ceasar cypher with given text and key"""
    c = ''
    x = x.upper()
    a = cencrypt(x, -y) #calling cencrypt function
    c = c + a
    return c #returning desired output
    
def vig_encrypt(x, y):
    """Vigenere cypher function, rotates alphabets in x by coresponding y alphbet's number times"""
    c = ''
    x = x.upper()
    y = y.upper()
    b = 0
    for a in x:
        if a in alphabets and b < len(x):
            g = y[b%len(y)]
            pos = alphabets.find(g)
            e = cencrypt(a , pos) #calling cencrypt function
            c = c + e
            b = b + 1
        else:
            c = c + a
    return c #returning desired output

def vig_decrypt(x, y):
    """Vigenere decrypt function, decrypts vigenere cypher if text and key are given """
    c = ''
    x = x.upper()
    y = y.upper()
    b = 0
    for a in x:
        if a in alphabets and b < len(x):
            g = y[b%len(y)]
            pos = alphabets.find(g) 
            e = cencrypt(a , -pos)  #calling cencrypt function
            c = c + e
            b = b + 1
        else:
            c = c + a
    return c #returning desired output
                
                
                
                
            
            
            
            
            
            
            
            
            
            
            
            