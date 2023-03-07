#ifndef helper_h
#define helper_h

#include <vector>

using namespace std;

struct Person {
    int id;
    int r,c;

    Person* next;
    Person* prev;

    Person(int id, Person* next, Person* prev) : id(id), next(next), prev(prev) {}
    Person(int id, int r, int c, Person* next, Person* prev) : id(id), next(next), prev(prev), r(r), c(c) {}
};

struct District {
    Person* first;

    int pop;

    District(Person* f) {
        first = f;
        pop = 1;
    }
};


#endif