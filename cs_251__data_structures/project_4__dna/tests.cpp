/*
 * tests.cpp
 * CS 251 - Project 4 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 */

#include <gtest/gtest.h>
#include "dna.h"

// testing the first/default constructor.
TEST(dna, constructor) {
    dna d;
    EXPECT_EQ(d.size(), 2);
    for (int i = 0; i < d.size(); i++) {
        EXPECT_EQ(d.at(i), 'X');
    }
    EXPECT_EQ(d.toString(), "XX");
    EXPECT_EQ(d.isLinked(), true);
}

// testing the second constructor.
TEST(dna, secondConstructor) {
    string dnastr = "AGATC";
    dna d(dnastr);
    EXPECT_EQ(d.isLinked(), true);
    EXPECT_EQ(d.toString(), dnastr);
    EXPECT_EQ(d.size(), dnastr.length());
    
    dna b("");  // checking for empty string.
    EXPECT_EQ(b.isLinked(), true);
    EXPECT_EQ(b.toString(), "");
    EXPECT_EQ(b.size(), 0);

    dnastr = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";  // checking for a larger string.
    dna c(dnastr);
    EXPECT_EQ(c.isLinked(), true);
    EXPECT_EQ(c.toString(), dnastr);
    EXPECT_EQ(c.size(), dnastr.size());
}

// testing the size.
TEST(dna, size) {
    dna a;  // for default constructor.
    EXPECT_EQ(a.size(), 2);

    dna b("");  // for empty string.
    EXPECT_EQ(b.size(), 0);

    dna c("ABCD");
    EXPECT_EQ(c.size(), 4);
}

// testing for the tostring function
TEST(dna, toString) {
    dna a;
    EXPECT_EQ(a.toString(), "XX");

    dna b("ABCD");
    EXPECT_EQ(b.toString(), "ABCD");

    string test = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    dna c(test);
    EXPECT_EQ(c.toString(), test);
}

// testing for the at function.
TEST(dna, at) {
    dna a;
    EXPECT_EQ(a.at(0), 'X');

    dna b("ABCD");
    EXPECT_EQ(b.at(0), 'A');  // checking specific instances.
    EXPECT_EQ(b.at(2), 'C');

    string test = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";  // checking with larger string.
    dna c(test);
    for (int i = 0; i < c.size(); i++) {
        EXPECT_EQ(c.at(i), test.at(i));
    }

    dna d("ABCD");
    d.at(0) = 'Z';  // attempting to change the value.
    d.at(3) = 'Y';
    EXPECT_EQ(d.at(0), 'Z');
    EXPECT_EQ(d.at(3), 'Y');
}

// testing the clear function.
TEST(dna, clear) {
    dna a;
    a.clear();  // clearing defaultly constructed dna.

    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.toString(), "");
    
    string test = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    dna b(test);
    b.clear();  // clearing larger string.

    EXPECT_EQ(b.size(), 0);
    EXPECT_EQ(b.toString(), "");
}

TEST(dna, copyConstructor) {
    dna a;
    dna b(a);  // calling as a function.

    ASSERT_EQ(b.isLinked(), true);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.toString(), b.toString());

    dna c("ABCD");
    dna d = c;  // calling using = operator.

    ASSERT_EQ(d.isLinked(), true);
    EXPECT_EQ(c.size(), d.size());
    EXPECT_EQ(c.toString(), d.toString());

    dna e("");
    dna f = e;  // copying empty dna.
    ASSERT_EQ(f.isLinked(), true);
    EXPECT_EQ(f.size(), e.size());
    EXPECT_EQ(f.toString(), e.toString());
    
    string dnastr = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";  // trying with a large string.
    dna g(dnastr);
    dna h = g;
    ASSERT_EQ(h.isLinked(), true);
    EXPECT_EQ(h.toString(), dnastr);
    EXPECT_EQ(h.size(), dnastr.size());
}

// testing equal operator.
TEST(dna, equalsOperator) {
    dna a;
    dna b("ABCD");
    a = b;
    ASSERT_EQ(a.isLinked(), true);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.toString(), b.toString());

    dna c("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    dna d;
    c = d;
    ASSERT_EQ(c.isLinked(), true);
    EXPECT_EQ(c.size(), d.size());
    EXPECT_EQ(c.toString(), d.toString());

    dna e;
    c.clear();
    e = c;  // copying a empty dna.
    ASSERT_EQ(e.isLinked(), true);
    EXPECT_EQ(e.size(), c.size());
    EXPECT_EQ(e.toString(), c.toString());

    dna f("");
    dna g("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    g = f;
    ASSERT_EQ(f.isLinked(), true);
    EXPECT_EQ(f.size(), g.size());
    EXPECT_EQ(f.toString(), g.toString());
    
    string dnastr = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    dna i(dnastr);
    dna h("1234");
    h = i;  // testing with a large string.
    ASSERT_EQ(h.isLinked(), true);
    EXPECT_EQ(h.toString(), dnastr);
    EXPECT_EQ(h.size(), dnastr.size());
}

// testing the equality operator.
TEST(dna, operatorEquality) {
    dna a, b;
    EXPECT_EQ(a == b, true);

    string test = "ABCD";
    dna c(test);
    dna d(test);
    EXPECT_EQ(c == d, true);

    test = "BCDA";
    dna e(test);
    EXPECT_EQ(c == e, false);
    EXPECT_EQ(a == e, false);
    EXPECT_EQ(e == e, true);

    dna f("");
    dna g("");
    EXPECT_EQ(f == g, true);  // empty dna shhould be equal.
    EXPECT_EQ(f == a, false);

    dna i("XXA");
    dna j("XX");
    EXPECT_EQ(i == j, false);
    EXPECT_EQ(j == a, true);  // defaultly constructed and j should be the same.
    
    string dnastr = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    dna k(dnastr);
    dna l = k;
    EXPECT_EQ(k == l, true);

    dna m("ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFJ");
    EXPECT_EQ(l == m, false);
}

TEST(dna, splice) {
    dna z("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    dna a = z;
    dna b("CDE");

    EXPECT_EQ(a.splice(b), true);  // removng from the middle.
    ASSERT_EQ(a.isLinked(), true);
    EXPECT_EQ(a.toString(), "ABFGHIJKLMNOPQRSTUVWXYZ");
    EXPECT_EQ(a.size(), 26 - 3);

    dna c = z;
    dna d("ABC");

    EXPECT_EQ(c.splice(d), true);  // removing from the front.
    ASSERT_EQ(c.isLinked(), true);
    EXPECT_EQ(c.size(), 26 - 3);
    EXPECT_EQ(c.toString(), "DEFGHIJKLMNOPQRSTUVWXYZ");

    dna e = z;
    dna f("XYZ");
    EXPECT_EQ(e.splice(f), true);  // removing from the end.
    ASSERT_EQ(e.isLinked(), true);
    ASSERT_EQ(e.size(), 26 - 3);
    ASSERT_EQ(e.toString(), "ABCDEFGHIJKLMNOPQRSTUVW");

    dna g = z;
    EXPECT_EQ(g.splice(z), true);  // removing the whole dna.
    ASSERT_EQ(g.isLinked(), true);
    EXPECT_EQ(g.size(), 0);
    EXPECT_EQ(g.toString(), "");

    dna h("ABCD");
    ASSERT_EQ(h.splice(z), false);

    dna i = z;
    dna j("");  // removing empty string.
    ASSERT_EQ(i.splice(j), false);

    dna k("1234");
    ASSERT_EQ(i.splice(k), false);   // removing string that is not present.

    dna l;
    ASSERT_EQ(i.splice(l), false);   // removing defaultly constructed dna.

    dna m("AA");
    ASSERT_EQ(i.splice(m), false);  // removing a string that has a character present.

    dna n("ZZ");
    ASSERT_EQ(i.splice(n), false);

    string dnastr = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string test2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
    dna o(dnastr);
    EXPECT_EQ(o.splice(z), true);  // removing a large string from a larger string.
    ASSERT_EQ(o.isLinked(), true);
    ASSERT_EQ(o.toString(), test2);
    ASSERT_EQ(o.size(), test2.size());
}
