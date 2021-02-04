//
//  Projct 1 GerryMandering, CS251
//  Name: Tanuj Dave, netId: tdave6
//
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include "ourvector.h"

using namespace std;

// struct that stores the data for a state.
struct State{
    string name = "DNE";
    string data;  // stores the information of state that is unprocessed.
    int numDistricts = 0, eligibleVoters = 0;
};

// loweres all the characters of the provided string and returns it.
string lowered(string theString) {
    for (int i = 0; i < theString.size(); ++i) {
        if (isalpha(theString.at(i))) {
            theString.at(i) = tolower(theString.at(i));
        }
    }
    return theString;
}

// counts the number of commas in 'line' and reutrns the amount.
int numberOfCommas(string line) {
    int ans = 0;

    for (int i = 0; i < line.size(); i++) {
        if (line.at(i) == ',') {
            ans++;
        }
    }
    return ans;
}

// takes the next integer in 'line' and puts it inside 'num', and moves to the
// next word/integer.
void processNextInt(string& line, int& num) {
    int pos = line.find(",");

    num = stoi(line.substr(0, pos));
    line.replace(0, pos + 1, "");
}

// takes the next word in 'line' and puts it inside 'text', and moves to the
// next word/integer.
void processNextString(string& line, string& text) {
    int pos = line.find(",");

    text = line.substr(0, pos);
    line.replace(0, pos + 1, "");
}

// searches for the state with name 'name' in 'theData' and returns a pointer
// to the state.
State* searchState(ourvector<State> &theData, State* theState, string name) {
    State* state;

    for (int i = 0; i < theData.size(); i++) {
        state = &theData.at(i);
        if (lowered(state->name) == lowered(name)) {
            return state;
        }
    }
    return theState;  // if state not found, remains the orignal.
}

// opens the file 'fileName' and reads data for districts and stores it in 
// 'theData', if stored then dataLoaded is set to true.
void readForDistricts(ourvector<State>& theData, string fileName, bool& dataLoaded) {
    ifstream file;
    State state;
    string line;
    string temp;

    file.open(fileName);
    if (!file.is_open()) {
        dataLoaded = false;
        cout << "Invalid first file, try again." << endl;
        return;
    }

    cout << "Reading: " << fileName << endl;
    while (!file.eof()) {
        getline(file, line);

        if (!file.fail()) {
            processNextString(line, state.name);
            state.numDistricts = (numberOfCommas(line) + 1) / 3;
            state.data = line;
            cout << "..." << state.name << "..." << state.numDistricts
                 << " districts total" << endl;
            theData.push_back(state);
            state.data.clear();
        }
    }
    file.close();
    dataLoaded = true;
}

// opens the file 'fileName' and reads data for voters and stores it in 
// the state in 'theData', if stored then dataLoaded is set to true.
void readForVoters(ourvector<State>& theData, string fileName, bool& dataLoaded) {
    ifstream file;
    State emptyState;
    string line, stateName;
    string temp;
    int voters = 0;

    file.open(fileName);
    if (!file.is_open()) {
        dataLoaded = false;
        cout << "Invalid second file, try again." << endl;
        return;
    }

    cout << "Reading: " << fileName << endl;

    while (!file.eof()) {
        getline(file, line);

        if (!file.fail()) {
            processNextString(line, stateName);

            State* state = searchState(theData, &emptyState, stateName);
            if (state->name == "DNE") {
                continue;
            }

            processNextInt(line, voters);
            state->eligibleVoters = voters;

            cout << "..." << stateName << "..." << state->eligibleVoters
                 << " eligible voters" << endl;
        }
    }

    file.close();
    dataLoaded = true;
}

// takes input for the file names and calls functions to load data.
void loadFiles(ourvector<State>& theData, bool& dataLoaded) {
    string fileName1, fileName2, buffer;
    
    cin >> fileName1 >> fileName2;
    cout << endl << "-----------------------------" << endl << endl;

    readForDistricts(theData, fileName1, dataLoaded);

    if (!dataLoaded) {
        return;
    }
    cout << endl;

    readForVoters(theData, fileName2, dataLoaded);
    cout << endl;
}

// loads the data of the 'theState' in 'stateData'.
void loadStateData(State* &theState, ourvector<int> &stateData) {
    int num, num1, num2;
    string line = theState->data;
    string buffer;

    int counter = 0;
    while (counter < theState->numDistricts) {
        processNextString(line, buffer);
        processNextInt(line, num1);  // for Democratic votes.
        processNextInt(line, num2);  // for Republican votes.

        // stores the percentage of Democratic votes.
        if (num1 + num2 == 0) {  // total votes are zero.
            num = -1;
        } else {
            num = 100 * num1 / (num1 + num2);
        }
        stateData.push_back(num);
        stateData.push_back(num1);
        stateData.push_back(num2);

        counter++;
    }
}

// takes state name's input and searches 'theData' for the state, calls
// functions to update pointer 'theState' and load 'stateData'.
void searchFiles(ourvector<State> &theData, State* &theState, ourvector<int> &stateData) {
    string stateName;
    State *temp = theState;

    getline(cin, stateName);

    cout << endl << "-----------------------------" << endl << endl;

    stateName = stateName.substr(1, stateName.size());

    if (theState == nullptr || lowered(theState->name) != lowered(stateName)) {
        theState = searchState(theData, nullptr, stateName);
        if (theState == nullptr) {
            cout << "State does not exist, search again." << endl << endl;
            theState = temp;
            return;
        }
        stateData.clear();  // clear stateData if different state.
        loadStateData(theState, stateData);
    }
}

// outputs the stats of 'theState' using its 'stateData'.
void stats(State* &theState, ourvector<int> &stateData) {
    int wastedDem = 0;
    int wastedRep = 0;
    int totalVotes = 0;
    double efficiency = 0;
    
    // calculating the wasted votes.
    for (int i = 0; i < stateData.size(); i += 3) {
        int demVotes = stateData.at(i + 1);
        int repVotes = stateData.at(i + 2);
        int overHalf = (demVotes + repVotes) / 2;
        totalVotes += demVotes + repVotes;

        if (overHalf != 0) {
            overHalf++;
            if (demVotes > repVotes) {
                wastedDem += demVotes - overHalf;
                wastedRep += repVotes;
            } else {
                wastedRep += repVotes - overHalf;
                wastedDem += demVotes;
            }
        }
    }
    efficiency = 100 * (wastedDem - wastedRep)/(totalVotes + 0.0);
    cout << "Gerrymandered: ";

    if (fabs(efficiency) < 7.0000 || theState->numDistricts < 3) {
        cout << "No" << endl;
    } else {
        cout << "Yes" << endl << "Gerrymandered against: ";
        if (efficiency < 0) {
            cout << "Republicans" << endl;
        } else {
            cout << "Democrats" << endl;
        }
        cout << "Efficiency Factor: " << fabs(efficiency) << "%" << endl;
    }

    cout << "Wasted Democratic votes: " << wastedDem << endl;
    cout << "Wasted Republican votes: " << wastedRep << endl;
    cout << "Eligible voters: " << theState->eligibleVoters << endl << endl;
}

// plots the districts for 'theState' using its 'stateData'.
void plotIt(State* &theState, ourvector<int> &stateData) {
    int val = 0;

    for (int i = 0; i < theState->numDistricts; i++) {
        cout << "District: " << i + 1 << endl;

        val = stateData.at(i * 3);
        if (val != -1) {
            cout << setfill('D') << setw(val) << ""
            << setfill('R') << setw(100-val) << "";
        }
        cout << setfill(' ') << endl;
    }

    cout << endl;
}

// described after main.
void returnRequiredDistrict(ourvector<int> &stateData, int &district,
                            int &theGap, int partyInt);
// described after main.
void customFunction(State* &theState, ourvector<int> &stateData);

// checks if state is loaded and returns the boolean.
bool checkIfStateLoaded(State* &theState) {
    string buffer;
    if (theState == nullptr) {
        cout << endl << "-----------------------------" << endl << endl;
        cout << "No state indicated, please search for state first."
             << endl << endl;
        return false;
    }
    return true;
}

// checks if the files are loaded adn returns the boolean.
bool checkIfFileLoaded(bool dataLoaded) {
    string buffer;
    if (dataLoaded) {
        getline(cin, buffer);
        cout << endl << "-----------------------------" << endl;
        cout << endl << "Already read data in, exit and start over." << endl
             << endl;
    }
    return dataLoaded;
}

// the function that handles all the inputs and command and call the functions
// for the commands. Paramenters ares the collection of the main parameters of
// the command functions.
void commandInput(ourvector<State>& theData, bool& exitCommand, bool& dataLoaded, State* &theState, ourvector<int> &stateData) {
    string command;
    string buffer;

    // print menu.
    cout << "Data loaded? ";
    if (dataLoaded) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    cout << "State: ";
    if (theState == nullptr) {
        cout << "N/A" << endl;
    } else {
        cout << theState->name << endl;
    }

    cout << endl << "Enter command: ";
    cin >> command;

    // checks and executes for the command.
    if (command == "exit") {
        exitCommand = true;
        cout << endl << "-----------------------------" << endl << endl;
    } else if (command == "load") {
        if (!checkIfFileLoaded(dataLoaded)) {
            loadFiles(theData, dataLoaded);
            theState = nullptr;
        }
    } else if (command == "search" && dataLoaded) {
        searchFiles(theData, theState, stateData);
    } else if (command == "stats" && dataLoaded) {
        if (checkIfStateLoaded(theState)) {
            cout << endl << "-----------------------------" << endl << endl;
            stats(theState, stateData);
        }
        getline(cin, buffer); // clears the cin for next input.
    } else if (command == "plot" && dataLoaded) {
        if (checkIfStateLoaded(theState)) {
            cout << endl << "-----------------------------" << endl << endl;
            plotIt(theState, stateData);
        }
        getline(cin, buffer);
    } else if (command == "winnable" && dataLoaded) {
        if (checkIfStateLoaded(theState)) {
            customFunction(theState, stateData);
        }
        getline(cin, buffer);
    } else if (!dataLoaded) {
        getline(cin, buffer);
        cout << endl << "-----------------------------" << endl << endl;
        cout << "No data loaded, please load data first." << endl << endl;
    }
}

int main() {
    bool dataLoaded = false, exitCommand = false;
    State* theState = nullptr;
    ourvector<int> stateData;
    ourvector<State> theData;

    cout << "Welcome to the Gerrymandering App!" << endl << endl;

    commandInput(theData, exitCommand, dataLoaded, theState, stateData);

    // main while loop
    while (!exitCommand) {
        commandInput(theData, exitCommand, dataLoaded, theState, stateData);
    }

    return 0;
}

// returns the qppropriate district in 'stateData' and updates 'district',
// 'theGap'.
void returnRequiredDistrict(ourvector<int> &stateData, int &district, int &theGap, int partyInt) {
    int difference = 0;
    
    theGap = fabs(stateData.at(1) -  stateData.at(2));
    for (int i = 3; i < stateData.size(); i+=3) {
        int num1 = stateData.at(i + 2);
        int num = stateData.at(i + 1);
        difference =  fabs(num - num1);

        if (theGap > difference && difference != 0) {
            if (partyInt == 1 && num1 > num) {
                theGap = difference;
                district = i / 3;
            } else if (partyInt == 0 && num > num1) {
                theGap = difference;
                district = i / 3;
            }
        }
    }
}

// enter the command 'winnable' followed by 'republicans' or 'democrats'
// fifth creative component command that outputs the district number in
// 'theState' for the party that they lost and has the least difference
// in the number of votes, thus outputs the district with the winnable odds,
// using 'stateData'.
void customFunction (State* &theState, ourvector<int> &stateData) {
    string party;
    int district;
    int theGap;

    cin >> party;
    party = lowered(party);

    cout << endl << "-----------------------------" << endl << endl;

    if (party == "republicans") {
        returnRequiredDistrict(stateData, district, theGap, 0);
    } else if (party == "democrats") {
        returnRequiredDistrict(stateData, district, theGap, 1);
    } else {
        cout << "Please enter either \"Republicans\" or \"Democrats\"." 
             << endl << endl;
        return;
    }

    cout << "District " << district
         << " is the district you should focus on!" << endl
         << endl;
}
