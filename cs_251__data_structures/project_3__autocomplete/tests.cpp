/*
 * test.cpp
 * CS 251 - Project 3 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 */

#include <iostream>
#include "AutocompleteList.h"

using namespace std;

// Tests getSize() on first constructor
bool size_test1() {
    cout << "in size_test1";
    AutocompleteList  list;  // empty list
    if (list.getSize() != 0) {
        return false;
    }
    cout << "...done" << endl;
    return true;
}
// Tests second constructor.
bool size_test2() {
    cout << "in size_test2";
    AutocompleteList  list(10);
    if (list.getSize() != 10) {
        return false;
    }

    AutocompleteList list2(-1); // test.cpp fails if this is not handled.
    cout << "...done" << endl;
    return true;
}

// Tests [] operator
bool operator_test() {
    cout << "in operator_test";
    AutocompleteList list(10);
    bool ans = false;

    for (int i = 0; i < 10; i++) {
        list[i].query = "hello";
        list[i].weight = i;
    }

    for (int i = 0; i < 10; i++) {
        if (list[i].query == "hello" && list[i].weight == i) {
            continue;
        } else {
            return false;
        }
    }

    cout << "...done" << endl;
    return true;
}

// tests constructor with filename.
bool filename_constructor_test() {
    cout << "in filename_constructor_test";
    AutocompleteList list("tiny.txt");
    
    if (list.getSize() != 6 ||
        list[0].query != "buck") {
        return false;
    }

    // testing for a large file.
    AutocompleteList list2("wiktionary.txt");

    if (list2.getSize() != 10000 ||
        list2[list2.getSize() - 1].query != "zone") {
        return false;
    }

    cout << "...done" << endl;
    return true;
}

// testing copy constructor.
bool copy_constructer_test() {
    cout << "in copy_constructer_test";
    AutocompleteList list("tiny.txt");
    AutocompleteList list2(list);

    if (list.getSize() != 6) {
        return false;
    }

    for (int i = 0; i < list2.getSize(); i++) {
        if (list2[i] != list[i]) {
            return false;
        }
    }

    cout << "...done" << endl;
    return true;
}

// testing copy operator.
bool copy_operator_test() {
    cout << "in copy_operator_test";
    AutocompleteList list("tiny.txt");
    AutocompleteList list2(0);

    list2 = list;
    if (list.getSize() != list2.getSize()) {
        return false;
    }

    for (int i = 0; i < list2.getSize(); i++) {
        if (list2[i] != list[i]) {
            return false;
        }
    }

    cout << "...done" << endl;
    return true;
}

// testing allMatches method.
bool allMatches_test1() {
    cout << "in allMatches_test1";
    AutocompleteList list("wiktionary.txt");
    AutocompleteList ans = list.allMatches("pret");
    AutocompleteList test;

    // if not the size of prefixes doesnt match copied correctly.
    if (ans.getSize() != 6) {
        return false;
    }

    // testing for a list with terms = nullptr.
    if (test.allMatches("").getSize() != 0) {
        return false;
    }

    cout << "...done" << endl;
    return true;
}

bool allMatches_test2(){
    cout << "in allMatches_test2";
    AutocompleteList list("small.txt");
    AutocompleteList ans = list.allMatches("february");
    
    // if the word found is first word in list
    // function may be checking out of bounds.
    if (ans[0].query != "february 2.0" || ans.getSize() != 1) {
        return false;
    }

    // if the word found is last word in list
    // function may be checking out of bounds.
    ans = list.allMatches("lamon");
    
    if (ans[ans.getSize() - 1].query != "lamonjabo" || ans.getSize() != 1){
        return false;
    }

    cout << "...done" << endl;
    return true;
}

bool allMatches_test3() {
    cout << "in allMatches_test3";
    AutocompleteList list("small.txt");
    AutocompleteList ans = list.allMatches("ja");
    // after last assignment ans has sort type weight, so empty
    // list should be returned.
    AutocompleteList ans2 = ans.allMatches("j");

    if (ans2.getSize() != 0) {
        return false;
    }

    cout << "...done" << endl;
    return true;
}

bool allMatches_test4() {
    cout << "in allMatches_test4";
    AutocompleteList list("small.txt");
    // if empty string is prefix, empty list should be returned.
    AutocompleteList ans = list.allMatches("");

    if (ans.getSize() != 0) {
        return false;
    }

    cout << "...done" << endl;
    return true;
}

bool allMatches_test5() {
    cout << "in allMatches_test5";
    AutocompleteList list("small.txt");
    // if prefix doesnt exist size should be zero.
    AutocompleteList ans = list.allMatches("Tanuj");

    if (ans.getSize() != 0) {
        return false;
    }

    cout << "...done" << endl;
    return true;
}

// testing numberOfMatches function.
bool numberOfMatches_test() {
    cout << "in numberOfMatches_test";
    AutocompleteList list("wiktionary.txt");
    AutocompleteList list2 = list.allMatches("pret");

    if (list.numberOfMatches("pret") != 6 ||
        list.numberOfMatches("") != 0 ||
        list.numberOfMatches("Tanuj") != 0) {
        return false;
    }

    if(list2.numberOfMatches("p") != 0) {
        return false;
    }
    cout << "...done" << endl;
    return true;
}

int main() {
    int passed = 0;
    int failed = 0;
    // Run tests
    
    cout << "Testing now..." << endl << endl;

    // testing begins.
    if (size_test1()) {
        passed++;
    } else {
        cout << endl
             << endl << "***size_test1 failed***" << endl
             << endl;
        failed++;
    }
    if (size_test2()) {
        passed++;
    } else {
        cout << endl
             << endl << "***size_test2 failed***" << endl
             << endl;
        failed++;
    }
    if (operator_test()) {
        passed++;
    } else {
        cout << endl
             << endl << "***operator_test failed***" << endl
             << endl;
        failed++;
    }
    if (filename_constructor_test()) {
        passed++;
    } else {
        cout << endl
             << endl << "***filename_constructor_test failed***" << endl
             << endl;
        failed++;
    }
    if (copy_constructer_test()) {
        passed++;
    } else {
        cout << endl
             << endl << "***copy_constructer_test failed***" << endl
             << endl;
        failed++;
    }
    if (copy_operator_test()) {
        passed++;
    } else {
        cout << endl
             << endl << "***copy_operator_test failed***" << endl
             << endl;
        failed++;
    }
    if (allMatches_test1()) {
        passed++;
    } else {
        cout << endl
             << endl << "***allMatches_test1 failed***" << endl
             << endl;
        failed++;
    }
    if (allMatches_test2()) {
        passed++;
    } else {
        cout << endl
             << endl << "***allMatches_test2 failed***" << endl
             << endl;
        failed++;
    }
    if (allMatches_test3()) {
        passed++;
    } else {
        cout << endl
             << endl << "***allMatches_test3 failed***" << endl
             << endl;
        failed++;
    }
    if (allMatches_test4()) {
        passed++;
    } else {
        cout << endl
             << endl << "***allMatches_test4 failed***" << endl
             << endl;
        failed++;
    }
    if (allMatches_test5()) {
        passed++;
    } else {
        cout << endl
             << endl << "***allMatches_test5 failed***" << endl
             << endl;
        failed++;
    }
    if (numberOfMatches_test()) {
        passed++;
    } else {
        cout << endl
             << endl << "***numberOfMatches_test failed***" << endl
             << endl;
        failed++;
    }
    //testing ends.

    cout << endl;
    cout << "Tests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;

    return 0;
}
