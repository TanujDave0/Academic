// graph.h <Starter Code>
// < Your name >
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
// University of Illinois at Chicago
// CS 251: Fall 2020
// Project #7 - Openstreet Maps
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:
  map<VertexT, map<VertexT, WeightT>> list; // set
  int size;

    bool _LookupVertex(VertexT v) const{
        return (list.count(v) != 0);
    }

 public:
  //
  // constructor:
  //
  // Constructs an empty graph where n is the max # of vertices
  // you expect the graph to contain.
  //
  // NOTE: the graph is implemented using an adjacency matrix.
  // If n exceeds the dimensions of this matrix, an exception
  // will be thrown to let you know that this implementation
  // will not suffice.
  //
  graph() {
    size = 0;
  }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    // return static_cast<int>(this->Vertices.size());
    return list.size();
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;

    for (auto v : list) {
        count += v.second.size();
    }

    return count;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
    // if (this->NumVertices() > MatrixSize) {  // we're full:
    //   return false;
    // }

    //
    // is the vertex already in the graph?  If so, we do not
    // insert again otherwise Vertices may fill with duplicates:
    //
    if (_LookupVertex(v)) {
      return false;
    }

    //
    // if we get here, vertex does not exist so insert.  Where
    // we insert becomes the rows and col position for this
    // vertex in the adjacency matrix.
    //
    map<VertexT, WeightT> emptyMap;
    list[v] = emptyMap;

    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    //
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
    if (!_LookupVertex(from) || !_LookupVertex(to)) {
        return false;
    }

    list[from][to] = weight;

    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    //
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
    if (!_LookupVertex(from) || !_LookupVertex(to)) {
        return false;
    }
    if (list.at(from).count(to) == 0) {
        return false;
    }

    weight = list.at(from).at(to);

    return true;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT>  S;

    //
    // we need to search the Vertices and find the position
    // of v, that will be the row we need in the adjacency
    // matrix:
    //
    if (!_LookupVertex(v)) {
        return S;
    }

    //
    // we found the row, so loop along the row and for every
    // edge that exists, add the column vertex to V:
    //
    // NOTE: how many columns are there?  The # of vertices.
    //
    for (auto node : list.at(v)) {
        S.insert(node.first);
    }

    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    // return this->Vertices;  // returns a copy:
    vector<VertexT> ans;

    for (auto v : list) {
        ans.push_back(v.first);
    }

    return ans;
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    // for (int i = 0; i < this->NumVertices(); ++i) {
    //   output << " " << i << ". " << this->Vertices[i] << endl;
    // }
    int i = 0;
    for (auto v : list) {
        output << " " << i << ". " << v.first << endl;
        i++;
    }
    

    output << endl;
    output << "**Edges:" << endl;
    for (auto v : list) {
        output << v.first << ": ";
        map<VertexT, WeightT> temp = list.at(v.first);
        for (auto node : temp) {
            output << "(" << v.first << "," << node.first << "," << node.second
                   << ") ";
        }
        output << endl;
    }
    output << "**************************************************" << endl;
  }
};
