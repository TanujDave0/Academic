/*
 * CS 251 - Project 2 - Fall 2
 * Name: Tanuj Dave, netId: tdave6
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include "myrandom.h"

using namespace std;

// printing the welcome message.
void welcomMessage() {
    cout << "Welcome to the Text Generator." << endl
         << "This program makes random text based on a document."
         << endl;
}

// cleares the newline after input.
void clearNewline() {
    string buffer;
    getline(cin, buffer);
}

// takes input fileName and checks if it exists.
void inputFile(ifstream &file, string &fileName) {
    cout << "Input file name?  ";
    cin >> fileName;
    clearNewline();
    file.open(fileName);

    while (!file.is_open()) {
        cout << "Invalid file, try again:  ";
        cin >> fileName;
        clearNewline();
        file.open(fileName);
    }
}

// takes input for N.
void inputN(int &N) {
    cout << "Value of N?  ";
    cin >> N;
    clearNewline();

    while (N <= 1) {
        cout << "N must be > 1, try again:  ";
        cin >> N;
        clearNewline();
    }
}

// takes input for the number of words user wants to generate.
void inputWords(int &length, int &N) {
    cout << "Total words you'd like to generate?  ";
    cin >> length;
    clearNewline();

    while (length < N) {
        cout << "Total words must be at least N, try again:  ";
        cin >> length;
        clearNewline();
    }
}

// takes input for the commands.
void inputCommand(string &command) {
    do {
    cout << "Type b-build map, p-print map, g-generate text, s-start over, x-to exit: ";
    cin >> command;
    clearNewline();
    } while (command != "b" && command != "p" &&
             command != "g" && command != "s" &&
             command != "x");
}

// builds the map using the file and closes it.
void buildMap(map<queue<string>, vector<string>> &theMap, ifstream &file, int &N, bool &built) {
    string temp;
    queue<string> tempKey;
    vector<string> tempValue;
    queue<string> firstKey;  // for wrapping around.

    // making the first key.
    for (int i = 0; i < N - 1; i++) {
        file >> temp;
        tempKey.push(temp);
        firstKey.push(temp);
    }

    while (file >> temp) {
        theMap[tempKey].push_back(temp);
        tempKey.pop();
        tempKey.push(temp);
    }

    // wrapping around.
    for (int i = 0; i < N - 1; i++) {
        theMap[tempKey].push_back(firstKey.front());
        tempKey.pop();
        tempKey.push(firstKey.front());
        firstKey.pop();
    }

    built = true;
    file.close();
}

// prints the map.
void printMap(map<queue<string>, vector<string>> theMap) {
    queue<string> tempKey;
    vector<string> tempValue;

    for (auto& q : theMap) {
        tempKey = q.first;  // taking the key.
        tempValue = q.second;  // taking its value.
        
        cout << "{";
        while (!tempKey.empty()) {  // for keys.
            if (tempKey.size() == 1) {
                cout << tempKey.front();
                tempKey.pop();
                break;
            }
            cout << tempKey.front() << " ";
            tempKey.pop();
        }
        cout << "} -> {";
        while (!tempValue.empty()) {  // for values.
            if (tempValue.size() == 1) {
                cout << tempValue.at(0);
                tempValue.erase(tempValue.begin());
                break;
            }
            cout << tempValue.at(0) << " ";
            tempValue.erase(tempValue.begin());
        }
        cout << "}" << endl;
    }
    cout << endl;
}

// returns a key randomly selected from theMap.
queue<string> randomKey(map<queue<string>, vector<string>> &theMap, int &high) {
    queue<string> ans;
    int counter = randomInteger(0, high);
    int i = 0;

    for (auto e : theMap) {
        ans = e.first;
        if (i == counter) {
            break;
        }
        i++;
    }

    return ans;
}

// generates the text by processing N grams process.
void generateText(map<queue<string>, vector<string>> &theMap, int &N, int &length) {
    queue<string> prefix = randomKey(theMap, theMap.size() - 1);
    queue<string> temp = prefix;  // for inserting first N - 1 words.
    string value;
    string text = "";

    for (int i = 0; i < prefix.size(); i++) {
        text.append(temp.front()+ " ");
        temp.pop();
    }

    for (int i = 0; i < length - N + 1; i++) {
        value = theMap[prefix].at(randomInteger(0, theMap[prefix].size() - 1));
        text.append(value);
        if (i + 1 != length - N + 1) {
            text.append(" ");
        }
        prefix.pop();
        prefix.push(value);
    }

    cout << "..." << text << "..." << endl << endl;
}

// the main function that handles all the input and function calls.
void commandInput(string &fileName, int &N, int &length, string &command, ifstream &file, bool &built, map<queue<string>, vector<string>> &theMap) {
    if (!built) {
        inputFile(file, fileName);
        inputN(N);
        inputWords(length, N);
    }

    inputCommand(command);
    cout << endl;

    switch (command[0]) {
        case 'b':
            cout << "...Building map: " << fileName << "..." << endl << endl;
            buildMap(theMap, file, N, built);
            break;
        case 'p':
            printMap(theMap);
            break;
        case 'g':
            generateText(theMap, N, length);
            break;
        case 's':
            built = false;
            theMap.clear();
            welcomMessage();
            break;
        case 'x':
            return;
    }
}

// main,
int main() {
    bool built = false;
    string fileName, command;
    int N = 0, length;
    ifstream file;
    map<queue<string>, vector<string>> theMap;

    welcomMessage();

    do {
        commandInput(fileName, N, length, command, file, built, theMap);
    } while (command != "x");

    return 0;
}
