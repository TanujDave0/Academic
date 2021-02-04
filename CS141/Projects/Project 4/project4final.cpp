//  main.cpp
//  Program 4
//
//  Created by Heet Parikh on 3/14/20.
//  Copyright © 2020 Heet Parikh. All rights reserved.
/* ----------------------------------------------------------- 
    Program 4: Two codes 
    
    Class: CS 141, Spring 2020.  Tues 4pm lab
    System: Gradescope
    Author: Heet Parikh netID: hparik5
    Partner: Tanuj Dave, netID: tdave6

         -----------------------------------------------------------
*/ 
#include <iostream>   // for cin and cout
#include <iomanip>    // for setw()
#include <cctype>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// removes newline and lowers the string.
string lowerStringAndRemoveNewLine(string line){
    string tempLine=line; // creating a temp line so that the orignal vector is not affected.

    for(int i=0; i<line.length();++i){
        tempLine[i]=tolower(line[i]);
        if(tempLine[i]=='\n'){
            tempLine[i]='\0';
        }
    }
    return tempLine;
}
 
// copies all the lines form the file into the vector.
void readLines(vector<string> &vectorOfLines){
    string line;
    ifstream theFIle;

    // opening the file.
    theFIle.open("ConstitutionAndBillOfRights.txt");
    if (!theFIle) {
        cout << "Unable to open file";
        exit(1); // terminate with error.
    }
    // lopp to get all the lines from the file.
    while (getline(theFIle,line)) {
        if(line.length()>1){
         vectorOfLines.push_back(line);
        }
    }
    theFIle.close(); // closing the file.
}

// takes the input from the user.
void phraseOrWordUserInput(string &phraseOrWordInput){
    cout<< "Enter word or phrase: ";
    getline(cin,phraseOrWordInput);
    lowerStringAndRemoveNewLine(phraseOrWordInput);
}

//compares for the given phrase or word in the vector(of the file), and
// assigns the line number to occurance.
void compareInputAndVector(const vector<string> vectorOfLines, string phraseOrWordInput,int& lineNumber){
    string tempLine; // creating a temp line so that the orignal vector is not affected.
    for(int i=0; i<vectorOfLines.size();++i){
        tempLine=lowerStringAndRemoveNewLine(vectorOfLines.at(i));
        if(tempLine.find(phraseOrWordInput) != string::npos){
            cout<<"Line "<<i<<':'<<endl;
            cout<<vectorOfLines.at(i)<<endl;
            lineNumber=i;
            break;
        }
    }
}

// printing the previous line if it exists.
void previousLines(const vector<string> vectorOfLines, int& lineNumber){
    lineNumber--; // decreasing the line number.
    if(lineNumber<0){ // if its out of bounds.
        cout<<"There is no previous file contents."<<endl;
        lineNumber++; // increasing it if its not in bounds.
    }
    else{ // if its in the bounds.
        cout<<"Line "<<lineNumber<<':'<<endl;
        cout<<vectorOfLines.at(lineNumber)<<endl;
    }
}
 
// printing the next line if it exists.
void followingLines(const vector<string> vectorOfLines, int& lineNumber){
    lineNumber++; // increasing it to next number.
    if(lineNumber>=vectorOfLines.size()){ // if its out of bounds.
        cout<<"There is no following file contents."<<endl;
        lineNumber--; // decreasing it if it wasnt in bounds.
    }
    else{ // if its int the bounds.
        cout<<"Line "<<lineNumber<<':'<<endl;
        cout<<vectorOfLines.at(lineNumber)<<endl;
    }
}

// printing all the occurances of the gievn phrase. 
void allOccurences(const vector<string> vectorOfLines, string phraseOrWordInput, int& lineNumber){
    string tempLine; // creating a temp line so that the orignal vector is not affected.
    for(int i=0; i<vectorOfLines.size();++i){
        tempLine=lowerStringAndRemoveNewLine(vectorOfLines.at(i));
        if(tempLine.find(phraseOrWordInput) != string::npos){
            cout<<"Line "<<i<<':'<<endl;
            cout<<vectorOfLines.at(i)<<endl;
            lineNumber=i; //assigning the line number.
        }
    }
}

//main function for the two codes.
void twoCodesMain(int& numberOfIteration, string& phraseOrWordInput, const vector<string> vectorOfLines, int& lineNumber){
    char menuOption;
    char carriageReturn;

    cin>>menuOption; // taking input for menu option.
    menuOption=toupper(menuOption); // upper casing it.
    carriageReturn = getchar(); // eliminate the carriage at the end of the line
    
    // all the switch cases for menu options.
    switch(menuOption){
            case 'W':
                phraseOrWordUserInput(phraseOrWordInput);
                compareInputAndVector(vectorOfLines,phraseOrWordInput,lineNumber);
                numberOfIteration++; // increasing number of iteration if its the first iteration.
                break;
            case 'P':
                previousLines(vectorOfLines,lineNumber);
                break;
            case 'F':
                followingLines(vectorOfLines, lineNumber);
                break;    
            case 'A':
                allOccurences(vectorOfLines, phraseOrWordInput,lineNumber);
                break;
            case 'X':
                cout << "Exiting program." << endl;
                exit( 0);
                break;
    }
}

// function to display the menu based on the number of iteration.
void displayMenu(int numberOfIteration){
    if(numberOfIteration==0){ // if its the first iteration.
        cout<< "Select from the following choices:  \n"
            << "  W  Enter word or phrase to find, and display enclosing text  \n"
            << "  X  Exit program \n"
            << "Your choice: ";
    }
    else{// if its not the first iteration.
        cout<< "Select from the following choices:  \n"
            << "  W  Enter word or phrase to find, and display enclosing text \n"
            << "  P  Display previous text \n"
            << "  F  Display following text \n"
            << "  A  Display all occurrences of found word or phrase \n"
            << "  X  Exit program \n"
            << "Your choice:  ";
        }
}
 
//main.
int main() {
    //declaring the variables.
    string phraseOrWordInput;
    vector<string> vectorOfLines;
    int numberOfIteration=0;
    int lineNumber=0;

    readLines(vectorOfLines); // creating the vector having lines from file.

    // loop to iterate unitl x is chosen (since it exits only if it is so).
    while(true){
        displayMenu(numberOfIteration); // displaying the menu.
        twoCodesMain(numberOfIteration, phraseOrWordInput, vectorOfLines, lineNumber); // doing the required.
    }
    return 0; // Thank you.
}