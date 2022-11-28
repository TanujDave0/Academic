# -*- coding: utf-8 -*-
"""
Created on Sat Dec  7 08:28:08 2019

@author: tanuj
"""

#Name:- Tanuj Dave
#UIN:- 665028452
#CS111 - Law

import geopandas as gpd
import pandas
import matplotlib.pyplot as plt

fileref = open('Crimes_-_2012_to_present.csv')
crimes = pandas.read_csv(fileref)
communities = gpd.read_file('Boundaries_Community.geojson')

def com_count(df, col, value, unique_id, com_num):
    """Returns count of unique_id in df com_num rows w/entry value in column col"""
    rows = df[df[col] == value] # boolean slice of rows we want
    if com_num not in rows['Community Area'].values:
        return 0
    grouped = rows.groupby('Community Area')
    return grouped[unique_id].count()[com_num]

def make_dictionary(df, col, value, unique_id):
    '''returns dictionary whose keys are community numbers and values are count of specified things '''
    dict1={}
    for i in range(1,78):
        dict1[i] = com_count(df, col, value, unique_id, i)
    return dict1

#plot1########################################################
dict1 = make_dictionary(crimes, 'Primary Type', 'OFFENSE INVOLVING CHILDREN', 'Case Number')
ls = []
for dig in communities['area_num_1']:
    dig = dict1[int(dig)]
    ls.append(dig)

communities['Total'] = ls

plt.figure(1)
fig, ax = plt.subplots() 
fig.set_size_inches (10, 10) 
communities.plot(column='Total', scheme='quantiles', edgecolor='black', ax=ax, legend=True, cmap='summer')
plt.title('Heat Map for Offense involving children!')

#plot2#######################################################
dict2 = make_dictionary(crimes, 'Primary Type', 'DECEPTIVE PRACTICE', 'Case Number')
ls2 = []
for dig in communities['area_num_1']:
    dig = dict2[int(dig)]
    ls2.append(dig)

communities['Total'] = ls2

plt.figure(2)
fig, ax = plt.subplots() 
fig.set_size_inches (10, 10) 
communities.plot(column='Total', scheme='quantiles', edgecolor='black', ax=ax, legend=True, cmap='summer')
plt.title('Heat Map for Deceptive Practicing!')


#plot3#######################################################
list1 = []
for ele in ls:
    add = ele/(max(ls))
    list1.append(add)

list2 = []
for ele in ls2:
    add2 = ele/(max(ls2))
    list2.append(add2)

list_final = []
for num in range(77):
    add3 = list1[num]*0.66 + list2[num]*0.34
    list_final.append(add3)
communities['Total'] = list_final

plt.figure(3)
fig, ax = plt.subplots() 
fig.set_size_inches (10, 10) 
communities.plot(column='Total', scheme='quantiles', edgecolor='black', ax=ax, legend=True, cmap='summer')
plt.title('Heat Map for Predictive Policing')

#text file###################################################
text = open('[tdave6]Project6.txt', 'w')
text.write('I consider offsence involving children to be serious and deceptive practicing to be of a lesser importance.\nWhile creating the map for Predictive Policing, I gave twice as much importance to offense involving children than Deceptive Practicing.\nSo, the appropriate ratio that would add upto 1 would be 0.333 and 0.666.\nThus, I arrived at 0.34 and 0.66 ratio for deceptive practicing to offense involving children.')
text.close()
fileref.close()
