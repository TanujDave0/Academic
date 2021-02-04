/*
 * application.cpp
 * CS 251 - Project 3 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 */

// enter c for cretive creative search
// when prompted, enter y if you want weights to print, n if do not want weights.
// After that enter the size of words >= 1 you want for the autocomplete when
// prompted. After that enter the prefix when prompted.
// prints the list creatively, if choice is y prints with weights, if n without
// weights. Depending on the size user want, size amount of queries are printed.
// alse checks if prefix entered is empty.

#include <iostream>
#include "AutocompleteList.h"

using namespace std;


// function to implement seach (autocomplete).
void search(bool &run, AutocompleteList data) {
    string prefix;

    cout << "Search: ";
    getline(cin, prefix);
    if (prefix == "#") {
        run = false;
        return;
    }

    data.allMatches(prefix).print(); // printing the list.
}

// prints the list creatively, if choice is y prints with weights, if n without
// weights. Depending on the size user want, size amount of queries are printed.
// alse checks if prefix entered is empty.
void creativeSearch(bool &run, AutocompleteList data, string choice, int size) {
    string prefix;

    cout << "Search: ";
    getline(cin, prefix);

    if (prefix == "#") {
        run = false;
        return;
    }

    while (prefix == "") {
        cout << "        ***please enter a valid prefix (non-empty)!***" << endl;
        getline(cin, prefix);
    }
    
    AutocompleteList ans = data.allMatches(prefix);
    if (ans.getSize() == 0) {
        cout << "        ***no words starting with " << prefix
             << "were found!***" << endl;
        return;
    }

    // if weights are required.
    if (choice == "y" || choice == "Y") {
        ans.printCreative(size, true);
    } else { // if not.
        ans.printCreative(size, false);
    }
}

// function that handles the commands and inputs and call function accordingly.
void commandInput(bool &run, string command, AutocompleteList data, string choice, int size) {
    if (command == "c") {
        creativeSearch(run, data, choice, size);
    } else {
        search(run, data);
    }
}

int main() {
    bool run = true;
    string filename, command, buffer;
    string prefix, choice;
    int size;
    
    cout << "Enter filename: ";
    cin >> filename;  // taking input for the filename.
    
    AutocompleteList data(filename);  // creating the list using the file.
    
    cout << "Enter s-search or c-creative search: ";
    cin >> command;

    getline(cin, buffer, '\n');
    if (command != "c" && command != "s") {
        return 0;
    }

    if(command != "c") {
        cout << "Welcome!" << endl
             << "Type your search below, press enter for autocomplete "
             << "(# to stop)."
             << endl;
    } else {
        cout << "Welcome!" << endl
             << "Type your search below, press enter for creaive-autocomplete "
             << "(# to stop)."
             << endl;
        
        cout << "Would you like the autocomplete with weights?"
             << " Enter (y/n): ";
        getline(cin, choice);  // taking choice for weights.

        // if incorrecty entered
        while ( !(choice == "y" || choice == "n" ||
                  choice == "Y" || choice == "N")) {
            cout << "Please enter y or n: ";
            getline(cin, choice);
        }

        cout << "Enter the limit of words to find for autocomplete: ";
        cin >> size;  // taking input for the size.

        // if incorrecty entered.
        getline(cin, buffer);
        while (size < 1) {
            cout << "Please enter a number >=1: ";
            cin >> size;
            getline(cin, buffer);
        }
    }

    // main loop
    do {
        commandInput(run, command, data, choice, size);
    } while (run);

    return 0;
}
