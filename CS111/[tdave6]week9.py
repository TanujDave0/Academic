# -*- coding: utf-8 -*-
"""
Created on Sat Oct 26 17:19:08 2019

@author: tanuj
"""
# netId = tdave6
# name =Tanuj Dave

def week9(inname, out1, out2):
    '''defining a function that takes 3 string inputs and takes certain number of lines out of inname file '''
    fileref = open(inname, encoding="ISO-8859-1")
    g1= out1 + '.txt'
    g2= out2 + '.txt'
    out1 = open(g1, 'w') #opening text file named out1 for writing
    out2 = open(g2, 'w') #opening text file named out2 for writing
    f = fileref.readlines() #reading file and making a list of lines in it
    out1.write(f[0]) #adding the first line
    out2.write(f[0]) #adding the first line
    for any in range(10, 19): #creating a loop to add 9 lines after first ten lines
        out1.write(f[any])
    for any in range(19, 37): #creating a loop to add 18 lines after first ninteen lines
        out2.write(f[any])
    out1.close()
    out2.close() #closing files
    fileref.close()

# The first line is crucial since it defines the name of columns
# The next 9 lines have information about first case
# The next 9 lines from there have information about case 2
# The next 18 lines after it have information aboout case 3 and case 4
# Thus each case uses 9 lines and first line defines names of columns
# we can do this to seperae the desired number of cases in a different file for further use in pandas or excel etc.