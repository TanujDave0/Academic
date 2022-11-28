/*
 * application.cpp
 * CS 251 - Project 4 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "dna.h"

using namespace std;

// a functiont that preocesses the next string from line and puts it into word.
void processNextString(string &line, string &word) {
    int pos = line.find(",");

    word = line.substr(0, pos);
    line.replace(0, pos + 1, "");
}

// a functiont that preocesses the next number from line and puts it into num.
void processNextInt(string &line, int &num) {
    int pos = line.find(",");

    num = stoi(line.substr(0, pos));
    line.replace(0, pos + 1, "");
}

// counting the number of words in the line.
int numWords(string line) {
    int ans = 0;

    for (int i = 0; i < line.size(); i++) {
        if (line.at(i) == ',') {
            ans++;  // increment if its a ','.
        }
    }

    return ans + 1;  // words would be num of commas + 1.
}

// reading the data from data file.
void readData(string &fileName, vector<string> &strands, map<vector<int>, string> &data) {
    ifstream file;
    string line;
    string word;
    int num;
    int size;
    vector<int> temp;

    file.open(fileName);

    // taking the strands fromt first line.
    getline(file, line);
    size = numWords(line);
    for (int i = 0; i < size; i++) {
        if (i == 0) {  // ignore first word.
            processNextString(line, word);
            continue;
        }
        processNextString(line, word);
        strands.push_back(word);
    }

    // processing all the data for each person.
    while (getline(file, line)) {
        processNextString(line, word);
        size = numWords(line);
        for (int i = 0; i < size; i++) {
            processNextInt(line, num);
            temp.push_back(num);
        }
        data[temp] = word;  // adding the person to the map.
        temp.clear();
    }

    file.close();
}

// searching if the dna belongs to someone in the data.
bool dnaFound(map<vector<int>, string> &data, dna &DNA, vector<string> &strands, string &name) {
    int num = 0;
    vector<int> seq;

    // doing for each strand.
    for (string dnastr: strands) {
        dna duplicate = DNA;
        num = 0;
        while (duplicate.splice(dnastr)) {  // counting presence of the strand.
            num++;
        }
        seq.push_back(num);
    }

    // going through data to find if someone matches.
    for (auto e: data) {
        if (seq == e.first) {  // if found.
            name = e.second;
            return true;
        }
    }

    return false;
}

int main() {
    string dataFileName;
    string dnaFileName;
    string name;
    vector<string> strands;  // storing all the strands.
    map<vector<int>, string> data;  // the data of dna of people.

    cout << "Welcome to the DNA Profiling App!" << endl;
    cout << "Enter database file: ";

    getline(cin, dataFileName);

    cout << "Enter dna file: ";

    getline(cin, dnaFileName);

    cout << endl;
    cout << "Searching database..." << endl;

    readData(dataFileName, strands, data);  // reading the data.

    ifstream file;
    string dnastr;

    file.open(dnaFileName);
    file >> dnastr;
    file.close();

    dna DNA(dnastr);  // creating the dna.

    if (dnaFound(data, DNA, strands, name)) {  // if dna matches.
        cout << "DNA match: " << name << endl;
    } else {                                   // if not.
        cout << "No match." << endl;
    }
}