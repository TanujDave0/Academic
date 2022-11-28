/*
 * dna.h
 * CS 251 - Project 4 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 */

#pragma once

#include <iostream>
#include <string>

using namespace std;

class dna {
private:
    //
    // This implementation is a doubly-linked structure.  The nodes are structs
    // called Nucleotides.  Size could keep track of how many Nucleotides are
    // currently in the list.  front should always point to the first
    // Nucleotide and back should point to the last one.
    struct Nucleotide {
        char value;
        Nucleotide *next;
        Nucleotide *prev;
    };
    int Size;
    Nucleotide *front;
    Nucleotide *back;

    //
    // findFirst: (private)
    //
    // Searches dna for the first copy of the sequence target, returning a
    // pointer to that occurrence or nullptr if the target sequence isn't
    // present.
    // Performance requirement:  this function doesn't have a set Big O target,
    // but should not time out on test cases and be reasonable.
    //
    Nucleotide* findFirst(dna target) {
        Nucleotide* node = this->front;
        Nucleotide* temp;
        Nucleotide* temp2;
        char first = target.at(0);

        // looping over each value to see if target matches.
        for (int i = 0; i < Size && i + target.size() - 1 < Size; i++) {
            if (node->value == first) {  // if the first char is found.
                bool ans = true;
                temp = node;  // using a temp as to keep node the same.
                temp2 = target.front;  // saves time compared to .at().
                for (int j = 0; j < target.size(); j++) {  // looking if the rest match.
                    if (temp->value != temp2->value) {
                        ans = false;
                        break;
                    }
                    temp = temp->next;  // moving to next.
                    temp2 = temp2->next;
                }
                if (ans) {
                    return node;  // if found.
                }
            }
            node = node->next;  // moving to next if not found.
        }

        return nullptr;  // if not found.
    }

public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create an empty dna object with two
    // Nucleotides, each with the value of 'X'.
    //
    dna() {
        front = new Nucleotide;  // creating the first node.
        front->value = 'X';  // setting the values to 'X'
        front->prev = nullptr;
        front->next = new Nucleotide;  // creating the second node.
        back = front->next;  // linking them.
        back->prev = front;
        back->next = nullptr;
        back->value = 'X';
        Size = 2;  // setting size approriately.
    }

    //
    // second constructor:
    //
    // Produces a new strand of nucleotides spelled out in the sequence given
    // by str.
    // Performance requirement: O(n)
    //
    dna(const string& str) {
        Nucleotide* temp = nullptr;
        Size = 0;
        front = nullptr;  // setting these in case its empty string.
        back = nullptr;

        for (int i = 0; i < str.size(); i++) {
            if (i == 0) {  // if the first iteration...
                temp = new Nucleotide;  // creating the first node.
                front = temp;
                temp->prev = nullptr;
            } else {       // if first node created...
                temp->next = new Nucleotide;
                temp->next->prev = temp;
                temp = temp->next;
            }
            Size++;
            temp->value = str[i];
            temp->next = nullptr;
        }
        back = temp;  // setting back appropriately as temp is the last node.
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create a dna object that contains a copy
    // of an existing dna object.
    // Performance requirement: O(n)
    //
    dna(const dna& other) {
        this->Size = other.Size;

        if (other.front == nullptr) {  // if it is empty dna.
            this->front = nullptr;
        }

        Nucleotide* temp = nullptr;
        Nucleotide* temp2;

        // looping over each element.
        for (int i = 0; i < Size; i++) {
            if (i == 0) {
                temp = new Nucleotide;
                this->front = temp;
                temp->prev = nullptr;
                temp2 = other.front;
            } else {
                temp->next = new Nucleotide;
                temp->next->prev = temp;
                temp = temp->next;
                temp2 = temp2->next;
            }
            temp->value = temp2->value;  // adding the value.
            temp->next = nullptr;
        }

        back = temp;  // setting back appropriately.
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by
    // the dna object.
    // Performance requirement: O(n)
    //
    virtual ~dna() {
        clear();  // would have same code as clear.
    }

    //
    // clear:
    //
    // Frees all memory in the chain of nucleotides in the dna obeject.  This
    // function should also set front, back, and Size, appropriately.
    // Performance requirement: O(n)
    //
    void clear() {
        Nucleotide* temp = front;

        // deleting each element.
        while (temp != nullptr) {
            front = front->next;
            delete temp;
            temp = front;
        }

        Size = 0;  // setting rest of the variables.
        back = nullptr;
    }
    
    //
    // operator=
    //
    // Called when you assign one dna object into another, i.e. this = other;
    // Performance requirement: O(n)
    //
    dna& operator=(const dna& other) {
        if (this == &other) {  // if setting equal to itself, saving time.
            return *this;
        }

        if (this->front != nullptr) {  // if not empty, need to clear memory.
            this->clear();
        }

        this->Size = other.Size;

        Nucleotide* temp = nullptr;
        Nucleotide* temp2;

        // setting each element.
        for (int i = 0; i < Size; i++) {
            if (i == 0) {  // if first iteration, creating head node.
                temp = new Nucleotide;
                this->front = temp;
                temp->prev = nullptr;
                temp2 = other.front;
            } else {
                temp->next = new Nucleotide;
                temp->next->prev = temp;
                temp = temp->next;
                temp2 = temp2->next;
            }
            temp->value = temp2->value;
            temp->next = nullptr;
        }

        this->back = temp;  // setting back.
        return *this;
    }
    
    //
    // size:
    //
    // Returns the # of Nucleotides currently in the dna strand.
    // Performance requirement: O(1)
    //
    int size() const {
        return Size;
    }
    
    //
    // at(i):
    //
    // Returns a reference to the ith Nucleotide's value, which allows
    // you to read (access) or write (modify) this value.  If i is out of
    // bounds, an exception is thrown.
    // Performance requirement: O(n)
    //
    char& at(int i) {
        if (i >= Size || i < 0) {  // if i is out of the range of the indexes.
            throw out_of_range("i out of range");
        }

        Nucleotide* temp = front;

        while(i > 0) {  // moving till the 'i'th element.
            temp = temp->next;
            i--;
        }

        return temp->value;  // returning pointer to the value.
    }
    
    //
    // toString:
    //
    // Returns a string spelling out the contents of the dna sequence.
    // Performance requirement: O(n)
    //
    string toString() const {
        string ans = "";  // if the dna is empty, return this.
        Nucleotide* temp = front;

        while (temp != nullptr) {
            ans.push_back(temp->value);  // adding each element.
            temp = temp->next;
        }

        return ans;  // returning the string.
    }
    
    //
    // operator==
    //
    // This operator determines how you define equality between two operators.
    // In this function, you should compare other and this.  The two objects
    // should be considered equal if they have the same sequence of values and
    // in the same order.
    // Performance requirement: O(n)
    //
    bool operator==(const dna& other) const {
        Nucleotide* temp;
        Nucleotide* temp2;

        if (this->Size != other.Size) {  // if the sizes are not equal...
            return false;  //...then dnas are not.
        }

        temp2 = other.front;
        temp = this->front;

        // checking each element.
        for (int i = 0; i < this->Size; i++) {
            if (temp->value != temp2->value) {
                return false;  // if not equal.
            }
            temp2 = temp2->next;
            temp = temp->next;  // moving to next if equal till now.
        }

        return true;
    }
    
    //
    // splice:
    //
    // Removes the first copy of the sequence in target that appears in the
    // dna sequence of current object.  This requires the linked structure to
    // be properly re-wired after removal.
    // Performance requirement: this function doesn't have a set Big O target,
    // but should not time out on test cases and be reasonable.
    //
    bool splice(dna target) {
        if (target.size() == 0 ||
            target.size() > this->Size) {
            return false;  // if target is empty dna or target is greater.
        }

        Nucleotide* temp = findFirst(target);
        if (temp == nullptr) {  // if target is not found.
            return false;
        }

        temp = temp->prev;  // if found, point to the node before the target.
        Nucleotide* temp2;

        if (temp != nullptr) {  // if string is not in the front.
            temp2 = temp->next;  // temp2 points to target's start.
        } else {
            temp2 = this->front;  // temp2 points to begining.
        }
        Nucleotide* temp3;

        // remove the target and free memeory.
        for (int i = 0; i < target.size(); i++) {
            temp3 = temp2;
            temp2 = temp2->next;
            delete temp3;
            Size--;
        }

        if (temp != nullptr) {  // if it is not the head.
            temp->next = temp2;
        } else {                // if it is the head.
            this->front = temp2;
            temp = nullptr;
        }
        if (temp2 != nullptr) {  // if we didnt remove from the end.
            temp2->prev = temp;
        } else {                 // if we removed from the end.
            temp2 = this->front;
            for (int i = 0; i < Size; i++) {  // setting back properly.
                this->back = temp2;
                temp2 = temp2->next;
            }
        }

        return true;
    }
    
    //
    // isLinked()
    //
    // Checks if a strand is linked correctly.  This is provided for you.
    // You should use it to test your linked structure often.
    // Performance requirement: O(n)
    //
    bool isLinked() {
        Nucleotide* start = front;
        // If we're at the start of a strand,
        // we should not have a previous pointer.
        if (start != nullptr && start->prev != nullptr) {
            return false;
        }
        // Walk the list, ensuring at each point that the next/prev pointers
        // are consistent with one another.
        for (Nucleotide* curr = start; curr != nullptr; curr = curr->next) {
            if (curr->next != nullptr && curr->next->prev != curr) {
                return false;
            }
            if (curr->prev != nullptr && curr->prev->next != curr) {
                return false;
            }
        }
        return true;
    }
};
