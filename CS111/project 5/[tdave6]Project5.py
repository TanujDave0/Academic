# -*- coding: utf-8 -*-
"""
Created on Mon Nov 25 15:44:18 2019

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
text.write('First 5 Rows \n')
text.write(str(twitter.head())+'\n'+'\n')
text.close()

g = nx.Graph()

g.add_edges_from(twitter.values)

text = open('[tdave6]Project5.txt', 'a')
text.write('number of edges = ' + str(g.number_of_edges())+'\n')
text.write('number of nodes = ' + str(g.number_of_nodes())+'\n\n')

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

text.write('\n the names and centrality values of the 10 most central nodes in the network'+ '\n' + str(pandas.Series(dict(nx.degree_centrality(g))).sort_values(ascending=False).head(10))+'\n')

text.write("\n degree_centrality_of_James = nx.degree_centrality(g)['James'] \n")

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

#Second Analysis

file = open('facebook_combined.csv', encoding='ISO-8859-1')
facebook = pandas.read_csv(file)
file.close()

text.write('\n \n \n Second Analysis \n')
text.write('First 5 Rows')
text.write(str(facebook.head())+'\n'+'\n')

g2 = nx.Graph()

g2.add_edges_from(facebook.values)

text.write('number of edges = ' + str(g2.number_of_edges())+'\n')
text.write('number of nodes = ' + str(g2.number_of_nodes())+'\n \n')

degree2 = pandas.Series(dict(nx.degree(g2)))

text.write('10 nodes with highest degree' + '\n' + str(degree2.sort_values(ascending=False).head(10)) + '\n')

plt.figure(5)
degree2.hist() 
plt.xlabel("Degree")
plt.ylabel("Count")
plt.title("Degree Distribution (noscaling) for second analysis")

plt.figure(6)
numpy.log10(degree2).hist()
plt.xlabel("Log base 10 of degree")
plt.title("Distribution of log base 10 of degrees for second analysis")

text.write('\n the names and centrality values of the 10 most central nodes in the network'+ '\n' + str(pandas.Series(dict(nx.degree_centrality(g2))).sort_values(ascending=False).head(10))+'\n')

g_cored2 = nx.k_core(g2, 3)

text.write('\n number of edges in cored graph = ' + str(g_cored2.number_of_edges())+'\n')

text.write('number of nodes in cored graph = ' + str(g_cored2.number_of_nodes())+'\n')

degree_of_cored_2 = pandas.Series(dict(nx.degree(g_cored2)))

plt.figure(7)
degree_of_cored_2.hist()
plt.title("3-cored graph degree distribution for second analysis")
plt.xlabel("Degree")
plt.ylabel("Count")

text.write('\n The 3 cored graph for second analysis is "Facebook-combined data" is really messy and has a lot of nodes, also takes about 30secs to display. Also has some dense areas which are further linked. But if we core it to 100, it has around 180 nodes')
text.close()

#plotting the 3-cored graph, but since it is really messy I commented it
#plt.figure(8, figsize=[9,9])
#nx.draw_networkx(g_cored2, with_labels=True)