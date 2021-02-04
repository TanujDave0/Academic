#ifndef island_h
#define island_h

#include <iostream>
#include "list.h"

using namespace std;

// class to store the data for each island.
class island {
private:
    myList<int> rides;  //linked list of the rides.
    bool visit; // status if visited for dfs adn bfs.
    int prev;  // predecessor for the bfs.

public:
    void insertNode(int num);  //inserting the ferry ride to num island.
    void deleteNode(int num);  // deleting the ride to island num.
    bool exist(int num);  // checking if ride to num island exists.
    void print();  // printing the list.
    void clear();  // clearing all the rides.
    bool visited();  // checking if isalnd is visited for dfs.
    void changeVisit(bool val);  // change visit value.
    int getNth(int pos);  // get the nth ferry ride.  
    int ferriesOut();  // returns the number of ferry rides.
    void changePrev(int pos);  // change the previously visited insland.
    int getPrev();  // return the previous island.
};

#endif