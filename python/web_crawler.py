# -*- coding: utf-8 -*-
"""
Created on Fri Nov 15 16:12:27 2019

@author: tanuj
"""

#Name :- TANUJ RAKESH DAVE
#UIN :- 665028452
#Project Web Crawler CS111 Law


import urllib.request as ur
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

def get_url(s):
    '''printing all the links in with href immediately after <a in given str''' 
    y = 0
    list = []
    if '<a href' in s:
        while y < s.rfind('<a href'):
            x = s.find('<a href', y)
            r = s.find('>', x)
            y = s.find('"', x+10, r)
            list.append(s[x+9:y])
    return list
        

def crawl(start, limit):
    '''Crawls from given page to 'limits' number of web pages and harvests unique email addresses '''
    to_visit = []
    visited = []
    emails = []
    to_visit.append(start)
    while to_visit:
        a = to_visit.pop()
        page = ur.urlopen(a)
        page_text = page.read()
        page_text = str(page_text)
        page.close()
        if a not in visited:
            list_emails = get_addresses(page_text)
            list_links = get_url(page_text)
            for email in list_emails:
                if email not in emails:
                    emails.append(email)
            for link in list_links:
                if link not in to_visit:
                    to_visit.append(link)
            visited.append(a)
            if len(visited) >= limit:
                break
    return emails