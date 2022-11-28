#include <iostream>
#include "list.h"

using namespace std;

// a stack class that inherits from linked list.
class myStack: public myList<int> {
private:
    // recursively print the stack.
    void _print(node* curr) {
        // if we reached the last element print it and return.
        if (curr->next() == nullptr) {
            cout << curr->val();
            return;
        }
        // since we store it as linked list, the topmost element
        // is the first, thus print the next first then this.
        _print(curr->next());
        cout <<  " - " << curr->val();
    }  
public:
    // remove the topmost element in the stack.
    void pop() {
        deleteNode(getBack()->val());  // since the topmost(last) element is at the end.
    }
    // return the topmost(last) element
    int front() {
        return getBack()->val();
    }
    // print the stack.
    void print() {
        _print(getHead()); // recursively print the stack.
        cout << endl;
    }
};