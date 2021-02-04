# -*- coding: utf-8 -*-
"""
Created on Fri Nov 22 22:25:24 2019

@author: tanuj
"""

import matplotlib.pyplot as plt
import pandas
import networkx as nx
import numpy 

g = nx.Graph()

g.add_node('Alice')
g.add_node('Bob')
g.add_node('Charlie')

g.add_edge('Alice', 'Bob')

degree = pandas.Series(dict(nx.degree(g)))
degree.hist()

nx.draw(g)