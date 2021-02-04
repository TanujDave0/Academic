//
//  main.cpp
//  ExampleCodeForGerrymander
//  Author:  Shanon Reckinger
//
//  Copyright ©2020 Shanon Reckinger. All rights reserved.
//
// partners: Tanuj Dave, Meet Shah, Waleed Khan.

#include <iostream>
#include <string>
#include "ourvector.h"
#include <fstream>

struct Student {
    string name = "DNE";
    double gpa;
    ourvector<double> gpas;
};

// declaring all functions for defining later.
void loadData(string filename, ourvector<Student> &students);
string getName(string &line);
double getGPA(string line);
void search(ourvector<Student> &students, Student &currStudent);
ourvector<double> getAllGpas(string line);
void printAll (Student currStudent);

using namespace std;

int main() {
    string filename = "input.txt";
    ourvector<Student> students;
    string buffer;
    Student currStudent;
    
    cout << "Welcome to the student GPA app!" << endl;
    cout << "Enter command: ";
    
    string command;
    cin >> command;
    
    while (command != "#"){
        if (command == "load"){
            getline(cin, filename);
            filename = filename.substr(1, filename.size());
            loadData(filename, students);
            
            for (auto &e : students){
                cout << e.name << ", GPA: " << e.gpa << endl;
            }
        }
        
        else if(command == "search"){
            search(students, currStudent);
        }
        
        else if(command == "printAll"){
            printAll(currStudent);
        }
        
        cout << "Enter command: ";
        cin >> command;
    }
    
    return 0;
}

// function to print all semesters' gpa. 
void printAll (Student currStudent) {
    if(currStudent.name != "DNE"){
        int counter = 1;
        for (auto &e : currStudent.gpas){
                cout << "Semester: " << counter << ", GPA: " << e << endl;
                counter++;
        }
    }
}

// seach for a student.
void search(ourvector<Student> &students, Student &currStudent){
    string name;
    getline(cin, name, '\n');
    Student temp;
    
    name = name.substr(1, name.size());
    
    for(Student student: students){
        if(student.name == name){
            cout << "Student Found: " << student.name<<endl;
            cout << "GPA: " << student.gpa <<endl;
            currStudent = student;
            return;
        }
    }
    
    cout<<"Student not found!"<<endl;
    currStudent = temp;
    
}

// gets all the gpas of current student.
ourvector<double> getAllGpas(string line) {
    int count = 0;
    ourvector<double> gpas;
    
    while (!line.empty()){
        count++;
        size_t pos = line.find(":");
        string semStr = line.substr(0, pos);
        line = line.substr(pos+1,line.size()-semStr.size()-1); 
        
        pos = line.find(":");
        string gpaStr;
        if ((int)pos == -1){ 
            gpaStr = line;
            line = "";
        } else {
            gpaStr = line.substr(0, pos); 
            line = line.substr(pos+1,line.size()-gpaStr.size()-1);
        }
        
        gpas.push_back(stod(gpaStr));
    }
    
    return gpas;
}

// loads the data required from the file.
void loadData(string filename, ourvector<Student> &students){
    ifstream inFile(filename);
    string line;
    Student student;
    getline(inFile, line, '\n');
    
    while (!inFile.eof()) {
        student.name = getName(line);
        student.gpa = getGPA(line);
        student.gpas = getAllGpas(line);
        students.push_back(student);
        getline(inFile, line, '\n');
    }
    
    inFile.close();
}

// returns the name of the student.
string getName(string &line) {
    size_t pos = line.find(":");
    string name = line.substr(0, pos); 
    line = line.substr(pos+1,line.size()-name.size()-1); 
    return name;
}

// returns the overall gpa of the student.
double getGPA(string line){
    int count = 0;
    double gpaSum = 0.0;
    
    while (!line.empty()){
        count++;
        size_t pos = line.find(":");
        string semStr = line.substr(0, pos);
        line = line.substr(pos+1,line.size()-semStr.size()-1); 
        
        pos = line.find(":");
        string gpaStr;
        if ((int)pos == -1){ 
            gpaStr = line;
            line = "";
        } else {
            gpaStr = line.substr(0, pos); 
            line = line.substr(pos+1,line.size()-gpaStr.size()-1);
        }
        gpaSum += stod(gpaStr);
    }
    return gpaSum / count;
}