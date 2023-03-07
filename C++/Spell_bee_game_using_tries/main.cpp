#include <iostream>
#include <vector>

#include "SBTrie.h"
#include "Trie.h"

using namespace std;

void getNewDictionary(SBTrie* sbt , string filename);
void updateDictionary(SBTrie* sbt , string filename);

void test0() {
    SBTrie *t = new SBTrie();

    updateDictionary(t, "lol.txt");
    cout << (t->wordCount() == 0) << 1 << endl;
    updateDictionary(t, "trial.txt");

    cout << t->getFromFile("lol.txt") << 0 << endl;
    cout << t->getFromFile("trial.txt") << 1 << endl;

    vector<string> *temp = t->words();
    cout << (*temp).size() << endl;
    for (string s : *temp) {
        cout << s << endl;
    }

    cout << endl;

    delete temp;
    delete t;
}

void test1() {
    SBTrie *t = new SBTrie();

    getNewDictionary(t, "trial.txt");

    cout << t->search("") << 0 << endl;
    cout << t->search("tanuj") << 1 << endl;
    cout << t->search("butter") << 0 << endl;
    cout << t->search("hi") << 1 << endl;
    cout << t->search("hiya") << 0 << endl;
    cout << (t->wordCount() == 8) << 1 << endl;

    cout << endl;
    delete t;
}

void test2() {
    SBTrie *t = new SBTrie();

    getNewDictionary(t, "trial.txt");

    cout << t->remove("") << 0 << endl;
    cout << t->remove("tanuj") << 1 << endl;
    cout << t->search("tanuj") << 0 << endl;
    cout << (t->wordCount() == 7) << 1 << endl;

    cout << endl;
    delete t;
}

void test3() {
    SBTrie *t = new SBTrie();

    updateDictionary(t, "trial.txt");

    // remove top
    cout << t->remove("road") << 1 << endl;
    cout << t->remove("road") << 0 << endl;
    cout << t->search("roadman") << 1 << endl;
    cout << t->search("road") << 0 << endl;
    cout << t->search("roadm") << 1 << endl;
    cout << (t->wordCount() == 7) << 1 << endl;
    cout << t->insert("road") << 1 << endl;
    cout << (t->wordCount() == 8) << 1 << endl;
    cout << t->search("roadman") << 1 << endl;
    cout << t->search("road") << 1 << endl;
    cout << t->search("roadm") << 1 << endl;

    cout << endl;
    delete t;
}

void test4() {
    SBTrie *t = new SBTrie();

    updateDictionary(t, "trial.txt");

    // remove mid
    cout << t->remove("roadm") << 1 << endl;
    cout << t->remove("roadm") << 0 << endl;
    cout << t->search("roadman") << 1 << endl;
    cout << t->search("road") << 1 << endl;
    cout << t->search("roadm") << 0 << endl;
    cout << (t->wordCount() == 7) << 1 << endl;
    cout << t->insert("roadm") << 1 << endl;
    cout << (t->wordCount() == 8) << 1 << endl;
    cout << t->search("roadman") << 1 << endl;
    cout << t->search("road") << 1 << endl;
    cout << t->search("roadm") << 1 << endl;

    cout << endl;
    delete t;
}

void test5() {
    SBTrie *t = new SBTrie();

    getNewDictionary(t, "trial.txt");

    // remove end
    cout << t->remove("roadman") << 1 << endl;
    cout << t->remove("roadman") << 0 << endl;
    cout << t->search("roadman") << 0 << endl;
    cout << t->search("road") << 1 << endl;
    cout << t->search("roadm") << 1 << endl;
    cout << (t->wordCount() == 7) << 1 << endl;
    cout << t->insert("roadman") << 1 << endl;
    cout << (t->wordCount() == 8) << 1 << endl;
    cout << t->search("roadman") << 1 << endl;
    cout << t->search("road") << 1 << endl;
    cout << t->search("roadm") << 1 << endl;

    cout << endl;
    delete t;
}

void test6() {
    SBTrie *t = new SBTrie();

    getNewDictionary(t, "trial.txt");

    cout << t->clear() << 1 << endl;
    cout << t->remove("road") << 0 << endl;
    cout << t->search("hi") << 0 << endl;
    cout << (t->wordCount() == 0) << 1 << endl;
    cout << t->clear() << 1 << endl;
    cout << (t->wordCount() == 0) << 1 << endl;

    cout << endl;
    delete t;
}

void test7() {
    SBTrie *t = new SBTrie();

    updateDictionary(t, "trial.txt");

    cout << (t->wordCount() == 8) << 1 << endl;
    cout << ((*(t->words())).size() == 8) << 1 << endl;
    cout << t->remove("") << 0 << endl;
    cout << ((*(t->words())).size() == 8) << 1 << endl;
    cout << t->remove("tanuj") << 1 << endl;
    cout << ((*(t->words())).size() == 7) << 1 << endl;
    cout << t->remove("roadm") << 1 << endl;
    cout << ((*(t->words())).size() == 6) << 1 << endl;
    cout << t->remove("roadm") << 0 << endl;
    cout << ((*(t->words())).size() == 6) << 1 << endl;
    cout << t->clear() << 1 << endl;
    cout << ((*(t->words())).size() == 0) << 1 << endl;

    cout << endl;
    delete t;
}


void test8() {
    SBTrie *t = new SBTrie();

    cout << t->new_set("AbcDEFg") << 1 << endl;
    cout << (t->current_set() == "abcdefg") << 1 << endl;
    cout << (t->new_set("h--i--j,k'lM;@N")) << 1 << endl;
    cout << (t->current_set() == "hijklmn") << 1 << endl;
    cout  << t->new_set("@@aa1b2b3c5c6dde8--effgg") << 0 << endl;
    cout << (t->current_set() == "hijklmn") << 1 << endl;
    cout << t->new_set("abccdefg") << 0 << endl;
    cout << (t->current_set() == "hijklmn") << 1 << endl;

    
    delete t;
}

int main() {
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    // test7();
}

void getNewDictionary(SBTrie* sbt , string filename) {
    // enter needed code here for command 1
    sbt->clear();
    if (!sbt->getFromFile(filename)) {
        sbt->clear();

        cout << "unable to read from the file" << endl;
    }
}

void updateDictionary(SBTrie* sbt , string filename) {
    // enter needed code here for command 2
    if (!sbt->getFromFile(filename)) {
        cout << "unable to read from the file" << endl;
    }
}