/*
 * AutocompleteList.h
 * CS 251 - Project 3 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 */
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

// struct to implement each term.
struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
    bool operator!=(const Term& term) const {
        return (query != term.query || weight != term.weight);
    }
};

// function for implementing sort using built in sort, for sorting lexicographically
bool sortByLexOrder (Term &a, Term &b) {
    return a.query < b.query;
}

// function for implementing sort using built in sort, for sorting by weight
bool sortByWeightOrder (Term &a, Term &b) {
    return a.weight > b.weight;
}

//
// AutocompleteList
//
class AutocompleteList {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted

    // implementing a binary search to find the string with the prefix.
    int binarySearch(string prefix) {
        int l = 0, r = this->size - 1, m = 0;
        string mid;

        while (l <= r) {
            m = (l + r)/2;
            mid = terms[m].query.substr(0, prefix.size());
            if (mid == prefix) {
                return m;
            } else if (mid < prefix) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }

        return -1; // if not found.
    }

    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int firstIndexOf(int pos, string prefix) {
        while (pos >= 0 && 
               this->terms[pos - 1].query.substr(0, prefix.size()) == prefix) {
            pos--;
        }
        return pos;
    }
    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int lastIndexOf(int pos, string prefix) {
        while (pos < getSize() &&
               this->terms[pos + 1].query.substr(0, prefix.size()) == prefix) {
            pos++;
        }
        return pos;  // TODO: update this
    }

 public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList() {
        this->terms = nullptr;
        this->size = 0;
        this->sortType = "none";
    }
    
    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList(int n) {
        if(n >= 0) {
            this->terms = new Term[n];
            this->size = n;
            this->sortType = "none";
        }
    }

    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    AutocompleteList(string filename) {
        ifstream file;
        string query;
        long long int weight;
        int N;

        file.open(filename);
        file >> N;

        this->terms = new Term[N];
        this->size = N;
        this->sortType = "lex";

        for (int i = 0; i < N; i++) {
            file >> this->terms[i].weight;
            getline(file, query);
            query.replace(0, 1, "");
            this->terms[i].query = query;
        }

        sort(terms, terms + this->size, sortByLexOrder); // sorting lexicographically
        file.close();
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        this->size = other.size;
        this->sortType = other.sortType;
        this->terms = new Term[this->size];

        for (int i = 0; i < other.size; i++) {
            this->terms[i].query = other.terms[i].query;
            this->terms[i].weight = other.terms[i].weight;
        }
    }

    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList& operator=(const AutocompleteList& other) {
        // if cpoying the same list.
        if (this == &other) {
            return *this;
        }

        if (terms != nullptr) {
            delete[] this->terms;
            terms = nullptr;
        }

        this->size = other.size;
        this->sortType = other.sortType;
        this->terms = new Term[this->size];

        for (int i = 0; i < other.size; i++) {
            this->terms[i].query = other.terms[i].query;
            this->terms[i].weight = other.terms[i].weight;
        }

        return *this;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    virtual ~AutocompleteList() {
        if (terms != nullptr) {
            delete[] terms;
        }
    }

    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() {
        return size;
    }

    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        if (i < 0 || i >= size) {
            throw out_of_range("AutocompleteList: i out of bounds");
        }

        return terms[i];
    }

    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        if (prefix == "" || this->sortType != "lex") {
            return AutocompleteList();
        }
        int pos = binarySearch(prefix);

        if (pos == -1) {
            return AutocompleteList();
        }

        int posL = firstIndexOf(pos, prefix);
        int posR = lastIndexOf(pos, prefix);
        AutocompleteList result(posR - posL + 1);
        
        for (int i = posL; i < posR + 1; i++) {
            result.terms[i - posL].query = this->terms[i].query;
            result.terms[i - posL].weight = this->terms[i].weight;
        }

        sort(result.terms, result.terms + result.size, sortByWeightOrder);
        return result;
    }

    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        if (prefix == "" || this->sortType != "lex") {
            return 0;
        }
        int pos = binarySearch(prefix);

        if (pos == -1) {
            return 0;
        }

        int posL = firstIndexOf(pos, prefix);
        int posR = lastIndexOf(pos, prefix);
        return posR - posL + 1;
    }

    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    void print() {
        if (terms == nullptr) {
            return;
        }
        for (int i = 0; i < getSize(); i++) {
            cout << "        " 
                 << terms[i].query << ", " << terms[i].weight << endl;
        }
    }
    
    // prints the list without weights.
    void printCreative(int size, bool weights) {
        if (terms == nullptr) {
            return;
        }
        if (weights) {
            for (int i = 0; i < getSize() && i < size; i++) {
            cout << "        " 
                 << terms[i].query << ", " << terms[i].weight << endl;
            }
        }
        else{
            for (int i = 0; i < getSize() && i < size; i++) {
                cout << "        " 
                     << terms[i].query << endl;
            }
        }
    }
};
