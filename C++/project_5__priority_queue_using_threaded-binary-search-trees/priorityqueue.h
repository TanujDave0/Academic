/*
 * priority.h
 * CS 251 - Project 5 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 */
#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)

    // function that adds a new leaf to the bst after the 'parent' node.
    void newLeaf(NODE* parent, T value, int priority, char pos) {
        NODE* leaf = new NODE;

        leaf->value = value;
        leaf->link = nullptr;
        leaf->right = nullptr;
        leaf->left = nullptr;
        leaf->dup = false;
        leaf->priority = priority;
        this->size++;

        leaf->parent = parent;  // linking the head and parent.
        if (pos == 'd') {  // if it is added as a duolicate.
            parent->link = leaf;
            parent->dup = true;
        } else if (pos == 'r') {  // if it is inserted as right child.
            parent->right = leaf;
        } else if (pos == 'l') {  // if it is inserted as a left child.
            parent->left = leaf;
        } else if (pos == 's') {  // if its the root.
            this->root = leaf;
            curr = nullptr;
        }
    }

    // create a string for the bst nodes recursively.
    void _toString(NODE* root, stringstream& ss) {
        if (root == nullptr) {
            return;
        }

        _toString(root->left, ss);  // go to left first.

        // add to the stream for the current node.
        ss << root->priority << " value: " << root->value << endl;

        _toString(root->link, ss);  // go to the link first.
        _toString(root->right, ss);  // go to right at the last.
    }

    // clear all the nodes of the bst recursively from the root given.
    void _clear(NODE* &root) {
        if (root == nullptr) {
            return;
        }

        _clear(root->left);  // clear the left first.
        _clear(root->right);  // clear tje right.
        _clear(root->link);  // clear the links lastly.

        size--;
        delete root;  // delete the current node.
        root = nullptr;  // set it to nullptr.
    }

    // checks if the two bsts are equal from the given nodes recursively.
    bool isEqual(NODE* first, NODE* second) const {
        // if both of them hold the same value, they are equal.
        if (first == second) {
            return true;
        } else if (first == nullptr || second == nullptr) {  // if both are not equal and either one of them is nullptr, then bsts are not the same.
                return false;
        }
        // if values are not the same, they are different.
        if (first->value != second->value) {
            return false;
        }
        // if both have the same duplicate values.
        if (first->dup == second->dup) {
            // if they have duplicates and linked lists are equal.
            if (first->dup && !isEqual(first->link, second->link)) {
                return false;
            }
        } else {  // if they have different dup values, then bsts are different.
            return false;
        }
        // if all true till now, recursively check left and right nodes.
        return isEqual(first->left, second->left) 
               && isEqual(first->right, second->right);
    }

    // set curr to the minimum node considering 'node' as root.
    void _begin(NODE* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        this->curr = node;
    }

    // recursively copy all the nodes from other bsts with root 'other'.
    void _copyAll(NODE* node, NODE* other) {
        if (node == nullptr) {  // if no root, return.
            return;
        }
        // if other has duplicates copy them first.
        if (other->dup) {
            NODE* temp = node;
            NODE* temp2 = other;
            // loop over the linked list.
            while (temp2->link != nullptr) {
                newLeaf(temp, temp2->link->value, temp2->link->priority, 'd');
                temp = temp->link;
                temp2 = temp2->link;
            }
        }
        // if there is a left node, copy it.
        if (other->left != nullptr) {
            // create a new leaf on the left for node.
            newLeaf(node, other->left->value, other->left->priority, 'l');
            // recursively copy the left of the bst.
            _copyAll(node->left, other->left);
        }

        // if there is a right node, copy it. 
        if (other->right != nullptr) {
            // create a new leaf on the right and copy the right bst recursively.
            newLeaf(node, other->right->value, other->right->priority, 'r');
            _copyAll(node->right, other->right);
        }
    }

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }
    
    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
        // if trying to copy itself, return.
        if (this == &other) {
            return *this;
        }

        clear();  // clear the bst for copying.
        size = 0;
        if (other.root == nullptr) {  // if copying a empty bst.
            root = nullptr;
            curr = nullptr;
            return *this;
        }
        
        NODE* otherPtr = other.root;
        // create the root.
        newLeaf(nullptr, otherPtr->value, otherPtr->priority, 's');
        _copyAll(this->root, otherPtr);  // recursively copy the rest.
        this->curr = nullptr;

        return *this;
    }
    
    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear() {
        _clear(root);  // recursively delete all the nodes.
    }
    
    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {
        _clear(root);  // recursively delete all the nodes.
    }
    
    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* present = root;  // pointer to the current node.
        NODE* prev = root;  // pointer ti the previous node.
        char pos = 's';  // assume that we need to insert as the root.

        // search for the node to insert after.
        while (present != nullptr) {
            prev = present;
            // if it has the same priority as the current node.
            if (priority == present->priority) {
                // if the current node already has duplicates
                if (present->dup) {
                    present = present->link;
                } else {  // if the current node doesnt have duplicates.
                    pos = 'd';
                    break;  // break out since we found the point of insertion.
                }
            } else if (priority < present->priority) {
                present = present->left;  // go to left if priority is lesser.
                pos = 'l';
            } else {
                present = present->right;  // go to the right if priority is greater.
                pos = 'r';
            }
        }

        // add the node with prev as the parent.
        newLeaf(prev, value, priority, pos);
    }
    // {}
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T dequeue() {
        // if no nodes to remove, return.
        if (root == nullptr || size == 0) {
            return T{};
        }

        // start the search for minimum prioritiy node from the left.
        NODE* node = root;
        while(node->left != nullptr) {
            node = node->left;
        }
        T valueOut = node->value;  // assign the return value.

        // // if node has duplicate.
        if (node->dup) {
            //linking the right child and the link.
            if (node->right != nullptr) {
                node->link->right = node->right;
                node->right->parent = node->link;
            }
            // linking the parent and the link.
            if (node->parent != nullptr) {
                if (node->parent->left == node) {  // if its the left sub child.
                    node->parent->left = node->link;
                } else {                          // if its the right sub child.
                    node->parent->right = node->link;
                }
            } else { // means that node was the root
                this->root = node->link;
            }
            node->link->parent = node->parent;
        } else if (node->right != nullptr) {  // if it has a child.
            // linking the parent and the child.
            if (node->parent != nullptr) {
                if (node->parent->left == node) {  // if its the left sub child.
                    node->parent->left = node->right;
                } else {                          // if its the right sub child.
                    node->parent->right = node->right;
                }
            } else { // means that node was the root
                this->root = node->right;
            }
            node->right->parent = node->parent;
        } else {                           // if it has no childs.
            if (node->parent != nullptr) {  // if it has a parent...
                if (node == node->parent->left) {  // link parent to the child.
                    node->parent->left = nullptr;
                } else {
                    node->parent->right = nullptr;
                }
            } else {                      // if it has no parent, and thus is the last node in the bst..
                this->root = nullptr;
            }
        }
        delete node;  // delete the node.
        size--;  // decrease the size.
        
        return valueOut;  // return the value we deleted.
    }
    
    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;  // return the size.
    }
    
    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
        _begin(root);  // recursively find the node with minimum priority.
    }
    
    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(?) - hard to say.  But approximately O(logn + m).  Definitely not O(n).
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int &priority) {
        // if we have no next defined.
        if (curr == nullptr) {
            return false;
        }

        // assign the return values.
        value = curr->value;
        priority = curr->priority;
        
        // if it has duplicates, move to the next duplicate.
        if (curr->dup) {
            curr = curr->link;
            return true;
        } 
        
        // moving back to the head of linked list if there is one.
        while (curr->parent != nullptr && curr->parent->link == curr) {
            curr = curr->parent;
        }
        
        if (curr->right != nullptr) { // if there is a right.
            _begin(curr->right);  // find the minimum node on the right.
            return true;
        } else { // if it has no right and duplicates.
            //move up till we find the next node.
            NODE* prev = nullptr;
            while (curr->parent != nullptr && curr->parent->left != curr) {
                prev = curr;
                curr = curr->parent;
            }
            // if we reached the root and we came from the right.
            if (curr->parent == nullptr && curr->right == prev) {
                curr = nullptr;
                return false;
            }
            curr = curr->parent;  // set the curr to the next in line.
            return true;
        }
        curr = nullptr;  // if we reached the end, set curr to null...
        return false;  // and return false.
    }
    
    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        stringstream ss;  // create a string stream for the string of the bst.

        _toString(root, ss);  // recursively create the string.

        return ss.str();  // return the string,
    }
    
    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek() {
        // find the minimum node from the root.
        NODE* node = root;
        // if empty, return.
        if (node == nullptr) {
            return T{};
        }
        while (node->left != nullptr) {
            node = node->left;
        }

        return node->value;  // return the value stored by the node.
    }
    
    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
        NODE* first = this->root;
        NODE* second = other.root;

        return isEqual(first, second);  // recursively check all the nodes.
    }
    
    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};
