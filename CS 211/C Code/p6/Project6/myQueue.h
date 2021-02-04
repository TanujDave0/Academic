#include <iostream>
#include "list.h"

using namespace std;

// a queue class that inherits from the linked list.
class myQueue: public myList<int> {
public:
    // removing the first element.
    void pop() {
        deleteNode(getHead()->val());  // since head is the first element.
    }
    // returning the first element.
    int getFront() {
        return getHead()->val();  // since head is the first element.
    }
};