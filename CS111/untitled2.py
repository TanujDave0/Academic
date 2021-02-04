# -*- coding: utf-8 -*-
"""
Created on Fri Nov 15 17:18:00 2019

@author: tanuj
"""

import urllib.request as ur

def open_html(a):
    page = ur.urlopen(a)
    page_text = page.read()
    #print(page_text)
    page_text = str(page_text)
    print(type(page_text))
    
    