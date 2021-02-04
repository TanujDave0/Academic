# -*- coding: utf-8 -*-
"""
Created on Thu Oct 31 21:17:13 2019

@author: tanuj dave
"""
#name : Tanuj Rakesh Dave
#UIN : 665028452
#NetID : tdave6

import pandas

def murder_plot(a):
    '''creating a function to plot required graphs from given input '''
    a += str('.csv')
    fileref = open(a,encoding='ISO-8859-1')
    chd = pandas.read_csv(fileref)
    #plot 1
    chd.plot(x='year',y=['Feb','Aug'])
    #plot 2
    chd.plot(x='year',y=['Feb','Aug','total'])
    fileref.close()

murder_plot('chicago-homicides')