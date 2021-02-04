# -*- coding: utf-8 -*-
"""
Created on Tue Oct 22 23:03:20 2019

@author: tanuj
"""

import pandas
import matplotlib.pyplot as plt
fileref = open('SCDB_2019_01_justiceCentered_Citation.csv',encoding='ISO-8859-1')
scdb = pandas.read_csv(fileref)

#Q1
scdb_subset = scdb[scdb.term>=2000]  #creating a subset for terms greater than and equal to the year 2000

#Q2
f = plt.figure(figsize=(25,25)) #making size 25" by 25"
scdb_subset.groupby('term')['caseId'].nunique().plot(kind='bar')  #plotting the graph for number of cases in each term from the year 2000
scdb_subset.groupby('term')['caseId'].nunique() # counting the number of cases in each term from the year 2000

#Q3
f = plt.figure(figsize=(25,25))  #making size 25" by 25"
scdb_subset.groupby(['justiceName','direction'])['vote'].count().plot(kind='bar') #plotting the graph for each justice's votes for directions from the term of 2000
scdb_subset.groupby(['justiceName','direction'])['vote'].count()  #counting the number of each justice's votes for directions from the term of 2000

#Q4
fileref = open('SCDB_2019_01_caseCentered_Citation.csv',encoding='ISO-8859-1') #opening new file for next questions
scdb = pandas.read_csv(fileref) 

scdb_subset2= scdb[scdb.term>=2006]  #creating a subset for terms greater than and equal to the year 2006

#Q5
f = plt.figure(figsize=(25,25))  #making size 25" by 25"
scdb_subset2.groupby('caseDisposition')['caseId'].count().plot(kind='bar')
scdb_subset2.groupby('caseDisposition')['caseId'].count()

#6
#plotted the graph for number of decesion-direct-dissent for each case-disposition after the term 2000

scdb_subset3= scdb[scdb.term>=2000]  #creating a subset for terms greater than and equal to the year 2000
f = plt.figure(figsize=(25,25))  #making size 25" by 25"
scdb_subset3.groupby('caseDisposition')['decisionDirectionDissent'].count().plot(kind='bar')
scdb_subset3.groupby('caseDisposition')['decisionDirectionDissent'].count()

#question 6 explanation - plotted the graph for number of decesion-direct-dissent for each case-disposition after the term 2000