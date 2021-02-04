#include <iostream>
#include "island.h"

using namespace std;

//inserting the ferry ride to num island.
void island::insertNode(int num) {
    if (rides.exists(num)) {
        cout << "Ferry ride already added!" << endl;
        return;
    }
    rides.insertNode(num);
}

// deleting the ride to island num.
void island::deleteNode(int num) {
    if (!rides.exists(num)) {
        cout << "Ferry ride does not exist" << endl;
        return;
    }
    rides.deleteNode(num);
}

// checking if ride to num island exists.
bool island::exist(int num) {
    return rides.exists(num);
}

// printing the list.
void island::print() {
    rides.print();
}

// clearing all the rides.
void island::clear() {
    rides.clear();
}

// checking if isalnd is visited for dfs.
bool island::visited() {
    return visit;
}

// change visit value.
void island::changeVisit(bool val) {
    visit = val;
}

// get the nth ferry ride.  
int island::getNth(int pos) {
    return rides.getNth(pos);
}

// returns the number of ferry rides.
int island::ferriesOut() {
    return rides.size();
}

// change the previously visited insland.
void island::changePrev(int pos) {
    prev = pos;
}

// return the previous island.
int island::getPrev() {
    return prev;
}