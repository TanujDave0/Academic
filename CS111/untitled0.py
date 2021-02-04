# -*- coding: utf-8 -*-
"""
Created on Mon Nov  4 15:06:03 2019

@author: tanuj
"""
import re

def get_addresses(content):
    '''Input can be either str type or bytes type from a urllib read'''
    #re package wants str type, not bytes
    strings = re.findall('[a-zA-Z0-9_.]*[@][a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+',str(content))
    #Some addresses have a trailing period. Need to get rid of it...
    for x in range(0, len(strings)):
        if strings[x].endswith("."):
            strings[x] = strings[x][0:len(strings[x])-1]
    return strings
