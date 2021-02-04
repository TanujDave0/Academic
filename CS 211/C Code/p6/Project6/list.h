#ifndef list_h
#define list_h

#include <iostream>

using namespace std;


// templating the class for saving space to write two similar classes.
// class to store a linked list of items.
template<typename T>
class myList {
    public:
    // insert a node.
    void insertNode(T num) {
        if (head == nullptr) { // if linked list is empty
            head = new node; // creating the head.
            head->setVal(num); // setting its values.
            head->setNext(nullptr);
            Size++;
            return;
        }
        node* curr = head;

        // iterate over the linked list till the end.
        while (curr->next() != nullptr) {
            curr = curr->next();
        }

        // add the node to the end.
        node* temp = new node;
        curr->setNext(temp);
        curr = curr->next();
        curr->setVal(num);
        curr->setNext(nullptr);
        back = curr; // back points to the end node.
        Size++;
    }
    // deleting the node with value num from list.
    void deleteNode(T num) {
        node* curr = head;
        node* prev = curr;
        // looping over to the node we need to delete.
        while (curr->val() != num) {
            prev = curr;
            curr = curr->next();
        }
        prev->setNext(curr->next());
        if (curr == head) {  // if there is only one element to delete.
            head = curr->next();
        }
        delete curr;
        curr = nullptr;
        if (prev->next() == nullptr) {
            back = prev; // updating the back.
        }
        Size--;
    }
    // for knowing the size.
    int size() {return Size;};
    // checking if there is a node with value num.
    bool exists(T num)  {
        node* curr = head;
        while (curr != nullptr) {
            if (curr->val() == num) {
                return true;
            }
            curr = curr->next();
        }
        return false;
    }
    // printing the whole list.
    // virtual so that child class can customise its own.
    virtual void print() {
        node* curr = head;
        cout << " -->  ";
        while (curr != nullptr) {
            cout << curr->val() << "  ";
            curr = curr->next();
        }
        cout << endl;
    }
    // clearing all the nodes.
    void clear() {
        _clear(head);
        head = nullptr;
        Size = 0;
    }
    // default constructor.
    myList() {
        head = nullptr;
        Size = 0;
    }
    // getter function to get the value at pos position.
    T getNth(int pos){
        if (pos >= Size || Size == 0) {
            return T{};
        }
        node* curr = head;
        while (pos > 0) {
            curr = curr->next();
            pos--;
        }
        return curr->val();
    }

    // a function to check if the list is empty.
    bool isEmpty() {
        return Size == 0;
    }
    
    protected:
        // for the classes that inherit from this class.

        // class to store each node.
        class node {
            private:
            T value;  // store the value of each node.
            node* nxt;  // store the pointer to next node.

            public:
            // getting the value.
            T val() {
                return value;
            }

            // getting the pointer to next node.
            node* next() {
                return nxt;
            }

            // setting the next node.
            void setNext(node* nxt) {
                this->nxt = nxt;
            }

            // setting the value.
            void setVal(T value) {
                this->value = value;
            }
        };

        // returns the head.
        // child class can access the pointer value but not change it.
        node* getHead() {
            return head;
        }

        // return the back.
        // child class can access the pointer value but not change it.
        node* getBack() {
            return back;
        }
    private:
        // function to recursively clear all the nodes.
        void _clear(node* curr) {
            if (curr == nullptr) {
                return;
            }
            _clear(curr->next());
            delete curr;
            curr = nullptr;
        }

        node* head;  // pointer to the head of the linked list.
        node* back;  // pointer to the end of the list.
        int Size;  // toring the size.
};

#endif