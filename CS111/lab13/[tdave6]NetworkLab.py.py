# -*- coding: utf-8 -*-
"""
Created on Fri Nov 22 21:15:05 2019

@author: tanuj
"""
#CS111 Law Lab Week 13

#Name:- Tanuj Rakesh Dave
#UIN:- 665028452
#NetID:- tdave6


import matplotlib.pyplot as plt
import pandas
import networkx as nx
import numpy 

file = open('twitter_cleaned.csv', encoding='ISO-8859-1')
twitter = pandas.read_csv(file)
file.close()

text = open('[tdave6]NetworkLab.txt', 'w')
text.write(str(twitter.head())+'\n'+'\n')
text.close()

g = nx.Graph()

g.add_edges_from(twitter.values)

text = open('[tdave6]NetworkLab.txt', 'a')
text.write('number of edges = ' + str(g.number_of_edges())+'\n')
text.write('number of nodes = ' + str(g.number_of_nodes())+'\n')

degree = pandas.Series(dict(nx.degree(g)))

text.write('10 nodes with highest degree' + '\n' + str(degree.sort_values(ascending=False).head(10)) + '\n')

plt.figure(1)
degree.hist() #graph 1
plt.xlabel("Degree")
plt.ylabel("Count")
plt.title("Degree Distribution (noscaling)")

plt.figure(2)
numpy.log10(degree).hist()
plt.xlabel("Log base 10 of degree")
plt.title("Distribution of log base 10 of degrees")

text.write('the names and centrality values of the 10 most central nodes in the network'+ '\n' + str(pandas.Series(dict(nx.degree_centrality(g))).sort_values(ascending=False).head(10))+'\n')

text.write("degree_centrality_of_James = nx.degree_centrality(g)['James']")

text.close()
