//
//  main.cpp
//  Oral Exam 1
//  CS 251, Reckinger, Fall 2020
//

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

void processNextString(string &line, string &data) {
    int pos = line.find(" ");
    
    data = line.substr(0, pos);
    line.replace(0, pos+1, "");
}

double processNextDouble(string line) {
    int pos = line.find(",");
    
    line = line.replace(pos, pos+1, "");
    // pos = line.find(".");
    // line = line.replace(pos, pos+1, "");\
    
    return stod(line);
    
}

void processLine(string line, string &year,double &price) {
    string priceStr;
    double temp;
    
    processNextString(line, year);
    price = processNextDouble(line);
    
}

void readFile(string &fileHeader,  map <string, double> &data) {
    ifstream file;
    string line;
    string year;
    double price;
    
    file.open("lab6_studA.txt");
    
    // if(file.is_open()) {
    //     cout<< "file is open" << endl;
    // }
    getline(file, fileHeader);
    cout<< fileHeader<<endl;
    for (int i=0; i < 30; i++){
        getline(file, line);
        processLine(line, year, price);
        data[year] = price;
    }
}

int main() {
    string fileHeader;
    map <string, double> data;
    // TODO:  Write your code here.
    
    readFile(fileHeader, data);
    
    for (auto e: data) {
        string a = e.first;
        double b = e.second;
        
        cout << a << " " << b << endl;
    }
    
    
    return 0;
}
