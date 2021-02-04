# -*- coding: utf-8 -*-
"""
Created on Sun Nov 24 19:46:18 2019

@author: tanuj
"""

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

text = open('[tdave6]Project5.txt', 'w')
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

g_cored = nx.k_core(g, 3)

text.write('number of edges in cored graph = ' + str(g_cored.number_of_edges())+'\n')

text.write('number of nodes in cored graph = ' + str(g_cored.number_of_nodes())+'\n')

degree_of_cored = pandas.Series(dict(nx.degree(g_cored)))

plt.figure(3)
degree_of_cored.hist()
plt.title("3-cored graph degree distribution")
plt.xlabel("Degree")
plt.ylabel("Count")

e = g_cored.nodes()
dict1 = {}
for ele in e:
    if type(ele) == str:
        eles=ele
        if len(ele) > 8:
            eles = ele[0:8] + '.'
        dict1[ele] = eles

plt.figure(4, figsize=[12,12])
nx.draw_networkx(g_cored, with_labels=True, labels=dict1)


