/*birth 0 0
birth 0 0
birth 0 0
birth 1 1
birth 1 1
birth 1 4
birth 4 4
*/

#include "GridWorld.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool test() {
    return false;
}

bool testConstructor() {
    GridWorld g1(5,6);
    GridWorld g2(11, 10);

    return g1.num_cols() == 6 && g1.num_rows() == 5 &&
            g2.num_cols() == 10 && g2.num_rows() == 11 &&
            g1.population() == 0 && g2.population() == 0;
}

bool testSimple() {
    GridWorld g1(4,4);
    int r = -1, c = -1;
    vector<int>* mem = g1.members(3, 3);
    vector<int>* mem2 = g1.members(-1, 0);
    vector<int>* mem3 = g1.members(0, -1);
    vector<int>* mem4 = g1.members(4, 0);
    vector<int>* mem5 = g1.members(0, 4);

    bool check = (*mem).size() == 0 &&
            (*mem2).size() == 0 &&
            (*mem3).size() == 0 &&
            (*mem4).size() == 0;
    
    delete mem;
    delete mem2;
    delete mem3;
    delete mem4;
    delete mem5;


    return  !g1.death(0) &&
            !g1.move(0, 3, 3) &&
            !g1.whereis(0, r, c) && r == -1 && c == -1 &&
            check;
}

bool testBirth() {
    GridWorld g1(5, 5);
    int id1 = -1;
    int id2 = -1;
    int id3 = -1;

    bool check1 = g1.birth(1,1, id1);
    bool check2 = g1.birth(-1,0,id2);
    bool check3 = g1.birth(0,-1,id3);

    return check1 && !check2 && !check3;
}

void print(string name, bool (*func)()) {
    cout << "Test for " << name << " has " << (func()? "passed": "*failed*") << endl;
}

int main() {

    cout << "Begining the tests" << endl << endl;

    print("testConstructor", &testConstructor);
    print("testSimple", &testSimple);
    
    return 0;
}