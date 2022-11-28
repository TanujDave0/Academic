/*
 * tests.cpp
 * CS 251 - Project 5 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *
 * to look at the test that go deeper than other, look at the int versions
 * of the functions. They are more thorough as compared to other data type's
 * functions.
 *
 */
#include <gtest/gtest.h>
#include "priorityqueue.h"

// testig for default constructor.
TEST(priorityqueue, defaultConstructor) {
    // declaring most types of priorityqueues for tesing.
    priorityqueue<int> a;
    priorityqueue<string> b;
    priorityqueue<char> c;
    priorityqueue<long long int> d;
    priorityqueue<double> e;

    //tesing size.
    EXPECT_EQ(a.Size(), 0);
    EXPECT_EQ(b.Size(), 0);
    EXPECT_EQ(c.Size(), 0);
    EXPECT_EQ(d.Size(), 0);
    EXPECT_EQ(e.Size(), 0);
 
    // testing using toSring. 
    EXPECT_EQ(a.toString(), "");
    EXPECT_EQ(b.toString(), "");
    EXPECT_EQ(c.toString(), "");
    EXPECT_EQ(d.toString(), "");
    EXPECT_EQ(e.toString(), "");
}
// testing for enqueue with int.
TEST(priorityqueue, enqueueInt) {
    // declaring an empty priorityqueue.
    priorityqueue<int> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i , i);
    }

    EXPECT_EQ(a.Size(), 4);
    EXPECT_EQ(a.toString(), "-2 value: -2\n-1 value: -1\n0 value: 0\n1 value: 1\n");
    
    // now testing for duplicates.
    priorityqueue<int> b;
    for (int i = -2; i < 2; i++) {
        b.enqueue(i , i);
        b.enqueue(i + 100, i);  // has same priority but different value.
    }
    EXPECT_EQ(b.Size(), 4 * 2);
    EXPECT_EQ(b.toString(), "-2 value: -2\n-2 value: 98\n-1 value: -1\n-1 value: 99\n0 value: 0\n0 value: 100\n1 value: 1\n1 value: 101\n");
}

// testing for enqueue with char.
TEST(priorityqueue, enqueueChar) {
    // declaring an empty priorityqueue.
    priorityqueue<char> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue('m' + i , i);
    }

    EXPECT_EQ(a.Size(), 4);
    // cout << "a" << a.toString();
    EXPECT_EQ(a.toString(), "-2 value: k\n-1 value: l\n0 value: m\n1 value: n\n");
    
    // now testing for duplicates.
    priorityqueue<char> b;
    for (int i = -2; i < 2; i++) {
        b.enqueue('m' + i, i);
        b.enqueue('m' + i + 10, i);  // has same priority but different value.
    }
    // cout << "b" << b.toString();
    EXPECT_EQ(b.Size(), 4 * 2);
    EXPECT_EQ(b.toString(), "-2 value: k\n-2 value: u\n-1 value: l\n-1 value: v\n0 value: m\n0 value: w\n1 value: n\n1 value: x\n");
}

// testing for enqueue with strings.
TEST(priorityqueue, enqueueString) {
    // declaring an empty priorityqueue.
    priorityqueue<string> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue("My num:" + to_string(i) , i);
    }

    EXPECT_EQ(a.Size(), 4);
    EXPECT_EQ(a.toString(), "-2 value: My num:-2\n-1 value: My num:-1\n0 value: My num:0\n1 value: My num:1\n");
    
    // now testing for duplicates.
    priorityqueue<string> b;
    for (int i = -2; i < 2; i++) {
        b.enqueue("MY num: " + to_string(i), i);
        b.enqueue("MY num: " + to_string(i + 10), i);  // has same priority but different value.
    }
    EXPECT_EQ(b.Size(), 4 * 2);
    EXPECT_EQ(b.toString(), "-2 value: MY num: -2\n-2 value: MY num: 8\n-1 value: MY num: -1\n-1 value: MY num: 9\n0 value: MY num: 0\n0 value: MY num: 10\n1 value: MY num: 1\n1 value: MY num: 11\n");
}

// testing for enqueue with doubles.
TEST(priorityqueue, enqueueDouble) {
    // declaring an empty priorityqueue.
    priorityqueue<double> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i + 1.9988 , i);
    }

    EXPECT_EQ(a.Size(), 4);
    EXPECT_EQ(a.toString(), "-2 value: -0.0012\n-1 value: 0.9988\n0 value: 1.9988\n1 value: 2.9988\n");
    
    // now testing for duplicates.
    priorityqueue<double> b;
    for (int i = -2; i < 2; i++) {
        b.enqueue(i + 1.9988 , i);
        b.enqueue(i + 1.9988 + 100, i);  // has same priority but different value.
    }
    EXPECT_EQ(b.Size(), 4 * 2);
    EXPECT_EQ(b.toString(), "-2 value: -0.0012\n-2 value: 99.9988\n-1 value: 0.9988\n-1 value: 100.999\n0 value: 1.9988\n0 value: 101.999\n1 value: 2.9988\n1 value: 102.999\n");
}

// testing for copy operatotr with int.
TEST(priorityqueue, copyOperatorInt) {
    // declaring an empty priorityqueue.
    priorityqueue<int> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i , i);
    }

    // creating a blank priorityqueue.
    priorityqueue<int> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a.Size(), b.Size());
    EXPECT_EQ(a.toString(), b.toString());
    
    // now testing for duplicates.
    priorityqueue<int> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue(i , i);
        c.enqueue(i + 100, i);  // has same priority but different value.
    }
    priorityqueue<int> d;
    d = c;
    EXPECT_EQ(c.Size(), d.Size());
    EXPECT_EQ(c.toString(), d.toString());
}

// testing for copy operatotr with char.
TEST(priorityqueue, copyOperatorChar) {
    // declaring an empty priorityqueue.
    priorityqueue<char> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue('m' + i, i);
    }

    // creating a blank priorityqueue.
    priorityqueue<char> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a.Size(), b.Size());
    EXPECT_EQ(a.toString(), b.toString());
    
    // now testing for duplicates.
    priorityqueue<char> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue('m' + i, i);
        c.enqueue('m' + i + 10, i);  // has same priority but different value.
    }
    priorityqueue<char> d;
    d = c;
    EXPECT_EQ(c.Size(), d.Size());
    EXPECT_EQ(c.toString(), d.toString());
}

// testing for copy operatotr with string.
TEST(priorityqueue, copyOperatorString) {
    // declaring an empty priorityqueue.
    priorityqueue<string> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue("MY num: " + to_string(i), i);
    }

    // creating a blank priorityqueue.
    priorityqueue<string> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a.Size(), b.Size());
    EXPECT_EQ(a.toString(), b.toString());
    
    // now testing for duplicates.
    priorityqueue<string> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue("MY num: " + to_string(i), i);
        c.enqueue("MY num: " + to_string(i + 10), i);  // has same priority but different value.
    }
    priorityqueue<string> d;
    d = c;
    EXPECT_EQ(c.Size(), d.Size());
    EXPECT_EQ(c.toString(), d.toString());
}

// testing for copy operatotr with double.
TEST(priorityqueue, copyOperatorDouble) {
    // declaring an empty priorityqueue.
    priorityqueue<double> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i + 1.9954 , i);
    }

    // creating a blank priorityqueue.
    priorityqueue<double> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a.Size(), b.Size());
    EXPECT_EQ(a.toString(), b.toString());
    
    // now testing for duplicates.
    priorityqueue<double> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue(i + 1.3232 , i);
        c.enqueue(i + 1.3232 + 100, i);  // has same priority but different value.
    }
    priorityqueue<double> d;
    d = c;
    EXPECT_EQ(c.Size(), d.Size());
    EXPECT_EQ(c.toString(), d.toString());
}

// testing for clear with int.
TEST(priorityqueue, clearInt) {
    //creating a priorityqueue and filling it up.
    priorityqueue<int> a;
    for (int i = -5; i < 10; i++) {
        a.enqueue(i, i);
    }
    a.clear();  // now clearing all the elements.
    EXPECT_EQ(a.Size(), 0);
    EXPECT_EQ(a.toString(), "");

    // now tesing for duplicates.
    priorityqueue<int> b;
    for (int i = -5; i < 10; i++) {
        a.enqueue(i, i);
        a.enqueue(i + 100, i);
    }
    b.clear();
    EXPECT_EQ(b.Size(), 0);
    EXPECT_EQ(b.toString(), "");

    // testing for a empty queue.
    priorityqueue<int> c;
    c.clear();
    EXPECT_EQ(c.Size(), 0);
    EXPECT_EQ(c.toString(), "");
}

// testing for clear with char.
TEST(priorityqueue, clearChar) {
    //creating a priorityqueue and filling it up.
    priorityqueue<char> a;
    for (int i = -5; i < 10; i++) {
        a.enqueue('m' + i, i);
    }
    a.clear();  // now clearing all the elements.
    EXPECT_EQ(a.Size(), 0);
    EXPECT_EQ(a.toString(), "");

    // now tesing for duplicates.
    priorityqueue<char> b;
    for (int i = -5; i < 10; i++) {
        a.enqueue('m' + i, i);
        a.enqueue('m' + i + 7, i);
    }
    b.clear();
    EXPECT_EQ(b.Size(), 0);
    EXPECT_EQ(b.toString(), "");

    // testing for a empty queue.
    priorityqueue<char> c;
    c.clear();
    EXPECT_EQ(c.Size(), 0);
    EXPECT_EQ(c.toString(), "");
}

// testing for clear with string.
TEST(priorityqueue, clearString) {
    //creating a priorityqueue and filling it up.
    priorityqueue<string> a;
    for (int i = -2; i < 2; i++) {
        a.enqueue("MY num: " + to_string(i), i);
    }
    a.clear();  // now clearing all the elements.
    EXPECT_EQ(a.Size(), 0);
    EXPECT_EQ(a.toString(), "");

    // now tesing for duplicates.
    priorityqueue<string> b;
    for (int i = -2; i < 2; i++) {
        b.enqueue("MY num: " + to_string(i), i);
        b.enqueue("MY num: " + to_string(i + 10), i);  // has same priority but different value.
    }
    b.clear();
    EXPECT_EQ(b.Size(), 0);
    EXPECT_EQ(b.toString(), "");

    // testing for a empty queue.
    priorityqueue<string> c;
    c.clear();
    EXPECT_EQ(c.Size(), 0);
    EXPECT_EQ(c.toString(), "");
}

// testing for clear with double.
TEST(priorityqueue, clearDouble) {
    //creating a priorityqueue and filling it up.
    priorityqueue<double> a;
    for (int i = -5; i < 10; i++) {
        a.enqueue(i + 1.8832, i);
    }
    a.clear();  // now clearing all the elements.
    EXPECT_EQ(a.Size(), 0);
    EXPECT_EQ(a.toString(), "");

    // now tesing for duplicates.
    priorityqueue<double> b;
    for (int i = -5; i < 10; i++) {
        a.enqueue(i + 1.8832, i);
        a.enqueue(i + 100 + 1.8832, i);
    }
    b.clear();
    EXPECT_EQ(b.Size(), 0);
    EXPECT_EQ(b.toString(), "");

    // testing for a empty queue.
    priorityqueue<double> c;
    c.clear();
    EXPECT_EQ(c.Size(), 0);
    EXPECT_EQ(c.toString(), "");
}

// testing for equality operator with int.
TEST(priorityqueue, equalityOperatorInt) {
    // declaring an empty priorityqueue.
    priorityqueue<int> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i , i);
    }

    // creating a blank priorityqueue.
    priorityqueue<int> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a == b, true);

    // now testing for duplicates.
    priorityqueue<int> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue(i , i);
        c.enqueue(i + 100, i);  // has same priority but different value.
    }
    priorityqueue<int> d;
    d = c;
    EXPECT_EQ(d == c, true);

    EXPECT_EQ(d == a, false);
    priorityqueue<int> e;  // testing with and for a empty queue.
    priorityqueue<int> f;

    EXPECT_EQ(d == e, false);
    EXPECT_EQ(e == f, true);

    // testing for a almost similar queue.
    priorityqueue<int> g;
    g = c;
    g.dequeue();
    EXPECT_EQ(g == c, false);
}

// testing for equality operator with char.
TEST(priorityqueue, equalityOperatorChar) {
    // declaring an empty priorityqueue.
    priorityqueue<char> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue('m' + i, i);
    }

    // creating a blank priorityqueue.
    priorityqueue<char> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a.Size(), b.Size());
    EXPECT_EQ(a.toString(), b.toString());
    
    // now testing for duplicates.
    priorityqueue<char> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue('m' + i, i);
        c.enqueue('m' + i + 10, i);  // has same priority but different value.
    }
    priorityqueue<char> d;
    d = c;
    EXPECT_EQ(d == c, true);

    EXPECT_EQ(d == a, false);
    priorityqueue<char> e;  // testing with and for a empty queue.
    priorityqueue<char> f;

    EXPECT_EQ(d == e, false);
    EXPECT_EQ(e == f, true);
}

// testing for equality operator with string.
TEST(priorityqueue, equalityOperatorString) {
    // declaring an empty priorityqueue.
    priorityqueue<string> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue("MY num: " + to_string(i), i);
    }

    // creating a blank priorityqueue.
    priorityqueue<string> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a.Size(), b.Size());
    EXPECT_EQ(a.toString(), b.toString());
    
    // now testing for duplicates.
    priorityqueue<string> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue("MY num: " + to_string(i), i);
        c.enqueue("MY num: " + to_string(i + 10), i);  // has same priority but different value.
    }
    priorityqueue<string> d;
    d = c;
    EXPECT_EQ(d == c, true);

    EXPECT_EQ(d == a, false);
    priorityqueue<string> e;  // testing with and for a empty queue.
    priorityqueue<string> f;

    EXPECT_EQ(d == e, false);
    EXPECT_EQ(e == f, true);
}

// testing for equality operator with double.
TEST(priorityqueue, equalityOperatorDouble) {
    // declaring an empty priorityqueue.
    priorityqueue<double> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i + 1.9954 , i);
    }

    // creating a blank priorityqueue.
    priorityqueue<double> b;
    b = a; // copying using copy opreator.
    EXPECT_EQ(a.Size(), b.Size());
    EXPECT_EQ(a.toString(), b.toString());
    
    // now testing for duplicates.
    priorityqueue<double> c;
    for (int i = -2; i < 2; i++) {
        c.enqueue(i + 1.3232 , i);
        c.enqueue(i + 1.3232 + 100, i);  // has same priority but different value.
    }
    priorityqueue<double> d;
    d = c;
    EXPECT_EQ(d == c, true);

    EXPECT_EQ(d == a, false);
    priorityqueue<double> e;  // testing with and for a empty queue.
    priorityqueue<double> f;

    EXPECT_EQ(d == e, false);
    EXPECT_EQ(e == f, true);
}

// testing for begin and next with int.
TEST(priorityqueue, beginNextInt) {
    // creating an empty queue.
    int value;
    int priority;
    priorityqueue<int> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i , i);
    }
    // without begin curr should return T{};
    EXPECT_EQ(a.next(value, priority), false);
    a.begin();  // begining it..
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.next(value, priority), i != 1);
        EXPECT_EQ(value, i);
        EXPECT_EQ(priority, i);
    }

    // checking next after done through all the nodes.
    EXPECT_EQ(a.next(value, priority), false);
    // checking with duplicates.
    priorityqueue<int> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue(i , i);
        b.enqueue(i + 100, i);  // has same priority but different value.
    }
    b.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.next(value, priority), true);
        EXPECT_EQ(value, i);
        EXPECT_EQ(priority, i);
        EXPECT_EQ(b.next(value, priority), i != 9);
        EXPECT_EQ(value, i + 100);
        EXPECT_EQ(priority, i);
    }

    // checking for starting again.
    b.begin();
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.next(value, priority), true);
        EXPECT_EQ(value, i);
        EXPECT_EQ(priority, i);
        EXPECT_EQ(b.next(value, priority), i != 9);
        EXPECT_EQ(value, i + 100);
        EXPECT_EQ(priority, i);
    }

    // checking for start over from the middle.
    priorityqueue<int> c;
    for (int i = -5; i < 10; i++) {
        c.enqueue(i , i);
        c.enqueue(i + 100, i);  // has same priority but different value.
    }
    c.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -5; i < 2; i++) {
        EXPECT_EQ(c.next(value, priority), true);
        EXPECT_EQ(value, i);
        EXPECT_EQ(priority, i);
        EXPECT_EQ(c.next(value, priority), i != 9);
        EXPECT_EQ(value, i + 100);
        EXPECT_EQ(priority, i);
    }
    c.begin();  // start again while next is pointing to a middle node.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(c.next(value, priority), true);
        EXPECT_EQ(value, i);
        EXPECT_EQ(priority, i);
        EXPECT_EQ(c.next(value, priority), i != 9);
        EXPECT_EQ(value, i + 100);
        EXPECT_EQ(priority, i);
    }
}

// testing for begin and next with char.
TEST(priorityqueue, beginNextChar) {
    // creating an empty queue.
    priorityqueue<char> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue('m' + i , i);
    }
    a.begin();
    char value;
    int priority;
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.next(value, priority), i != 1);
        EXPECT_EQ(value, 'm' + i);
        EXPECT_EQ(priority, i);
    }
    
    // checking with duplicates.
    priorityqueue<char> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue('m' + i , i);
        b.enqueue('m' + i + 9, i);  // has same priority but different value.
    }
    b.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.next(value, priority), true);
        EXPECT_EQ(value, 'm' + i);
        EXPECT_EQ(priority, i);
        EXPECT_EQ(b.next(value, priority), i != 9);
        EXPECT_EQ(value, 'm' + i + 9);
        EXPECT_EQ(priority, i);
    }
}

// testing for begin and next with string.
TEST(priorityqueue, beginNextString) {
    // creating an empty queue.
    priorityqueue<string> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue("MY num: " + to_string(i), i);
    }
    a.begin();
    string value;
    int priority;
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.next(value, priority), i != 1);
        EXPECT_EQ(value, "MY num: " + to_string(i));
        EXPECT_EQ(priority, i);
    }
    
    // checking with duplicates.
    priorityqueue<string> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue("MY num: " + to_string(i), i);
        b.enqueue("MY num: " + to_string(i + 10), i);  // has same priority but different value.
    }
    b.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.next(value, priority), true);
        EXPECT_EQ(value, "MY num: " + to_string(i));
        EXPECT_EQ(priority, i);
        EXPECT_EQ(b.next(value, priority), i != 9);
        EXPECT_EQ(value, "MY num: " + to_string(i + 10));
        EXPECT_EQ(priority, i);
    }
}

// testing for begin and next with double.
TEST(priorityqueue, beginNextDouble) {
    // creating an empty queue.
    priorityqueue<double> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i + 1.8899 , i);
    }
    a.begin();
    double value;
    int priority;
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.next(value, priority), i != 1);
        EXPECT_EQ(value, i + 1.8899);
        EXPECT_EQ(priority, i);
    }
    
    // checking with duplicates.
    priorityqueue<double> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue(i + 1.8899 , i);
        b.enqueue(i + 1.8899 + 100, i);  // has same priority but different value.
    }
    b.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.next(value, priority), true);
        EXPECT_EQ(value, i + 1.8899);
        EXPECT_EQ(priority, i);
        EXPECT_EQ(b.next(value, priority), i != 9);
        EXPECT_EQ(value, i + 1.8899 + 100);
        EXPECT_EQ(priority, i);
    }
}

// testing for dequeue with int.
TEST(priorityqueue, dequeueInt) {
    // creating an empty queue.
    priorityqueue<int> a;
    int value, priority;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i , i);
    }
    // clearing just 1 element.
    a.dequeue();
    EXPECT_EQ(a.Size(), 3);
    EXPECT_EQ(a.toString(), "-1 value: -1\n0 value: 0\n1 value: 1\n");

    // clearing all the elements.
    for (int i = -1; i < 2; i++) {
        a.dequeue();
        EXPECT_EQ(a.Size(), 2 - i - 1);  // checking if size is also decreased properly.
    }
    EXPECT_EQ(a.Size(), 0);  // final size should be 0;

    // checking with duplicates.
    priorityqueue<int> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue(i , i);
        b.enqueue(i + 100, i);  // has same priority but different value.
    }
    // checking if the operaion returns the next correctly and begin is set correctly.
    int size = b.Size();
    for (int i = -5; i < 10; i++) {
        b.begin();  // begin every time to check if removed correctly.
        EXPECT_EQ(b.next(value, priority), true);
        EXPECT_EQ(value, i);
        EXPECT_EQ(priority, i);

        b.dequeue();  // dequeue the next element.
        EXPECT_EQ(b.Size(), --size);  // check if size is decremented

        b.begin();
        EXPECT_EQ(b.next(value, priority), i != 9);
        EXPECT_EQ(value, i + 100);
        EXPECT_EQ(priority, i);

        b.dequeue();  // dequeue the next element.
        EXPECT_EQ(b.Size(), --size);  // check if size is decremented
    }

    // trying to clear an empty queue.
    priorityqueue<int> c;
    c.dequeue();
    EXPECT_EQ(c.toString(), "");
    EXPECT_EQ(c.Size(), 0);  // size and default construction should not be different after dequeue.
}

// testing for dequeue with char.
TEST(priorityqueue, dequeueChar) {
    // creating an empty queue.
    priorityqueue<char> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue('m' + i , i);
    }
    // clearing just 1 element.
    a.dequeue();
    EXPECT_EQ(a.Size(), 3);
    EXPECT_EQ(a.toString(), "-1 value: l\n0 value: m\n1 value: n\n");

    // clearing all the elements.
    for (int i = -1; i < 2; i++) {
        a.dequeue();
        EXPECT_EQ(a.Size(), 2 - i - 1);  // checking if size is also decreased properly.
    }
    EXPECT_EQ(a.Size(), 0);  // final size should be 0;

    // checking with duplicates.
    priorityqueue<char> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue('m' + i , i);
        b.enqueue('m' + i + 100, i);  // has same priority but different value.
    }
    b.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    int size = b.Size();
    for (int i = -5; i < 10; i++) {
        b.dequeue();
        EXPECT_EQ(b.Size(), --size);
        b.dequeue();
        EXPECT_EQ(b.Size(), --size);
    }
}

// testing for dequeue with string.
TEST(priorityqueue, dequeueString) {
    // creating an empty queue.
    priorityqueue<string> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue("My num: " + i , i);
    }
    // clearing just 1 element.
    a.dequeue();
    EXPECT_EQ(a.Size(), 3);
    EXPECT_EQ(a.toString(), "-1 value: \n0 value: My num: \n1 value: y num: \n");

    // clearing all the elements.
    for (int i = -1; i < 2; i++) {
        a.dequeue();
        EXPECT_EQ(a.Size(), 2 - i - 1);  // checking if size is also decreased properly.
    }
    EXPECT_EQ(a.Size(), 0);  // final size should be 0;

    // checking with duplicates.
    priorityqueue<string> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue("My num: " + i , i);
        b.enqueue("My num: " + i + 100, i);  // has same priority but different value.
    }
    b.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    int size = b.Size();
    for (int i = -5; i < 10; i++) {
        b.dequeue();
        EXPECT_EQ(b.Size(), --size);
        b.dequeue();
        EXPECT_EQ(b.Size(), --size);
    }
}

// testing for dequeue with double.
TEST(priorityqueue, dequeueDouble) {
    // creating an empty queue.
    priorityqueue<double> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i + 1.5566 , i);
    }
    // clearing just 1 element.
    a.dequeue();
    EXPECT_EQ(a.Size(), 3);
    EXPECT_EQ(a.toString(), "-1 value: 0.5566\n0 value: 1.5566\n1 value: 2.5566\n");

    // clearing all the elements.
    for (int i = -1; i < 2; i++) {
        a.dequeue();
        EXPECT_EQ(a.Size(), 2 - i - 1);  // checking if size is also decreased properly.
    }
    EXPECT_EQ(a.Size(), 0);  // final size should be 0;

    // checking with duplicates.
    priorityqueue<double> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue(i + 1.5566 , i);
        b.enqueue(i + 1.5566 + 100, i);  // has same priority but different value.
    }
    b.begin();
    // checking if the operaion returns the next correctly and begin is set correctly.
    int size = b.Size();
    for (int i = -5; i < 10; i++) {
        b.dequeue();
        EXPECT_EQ(b.Size(), --size);
        b.dequeue();
        EXPECT_EQ(b.Size(), --size);
    }
}

// testing for peek with int.
TEST(priorityqueue, peekInt) {
    // creating an empty queue.
    priorityqueue<int> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i , i);
    }
    // looking at the min node.
    EXPECT_EQ(a.peek(), -2);
    
    // testing peeking using dequeue.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.peek(), i);
        a.dequeue();
    }

    // testing after all nodes removed.
    EXPECT_EQ(a.peek(), int{});

    // checking with duplicates.
    priorityqueue<int> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue(i , i);
        b.enqueue(i + 100, i);  // has same priority but different value.
    }
    // looking at the min node.
    EXPECT_EQ(b.peek(), -5);
    
    // testing peeking using dequeue.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.peek(), i);
        b.dequeue();
        EXPECT_EQ(b.peek(), i + 100);
        b.dequeue();
    }

    // testing if peek messes with curr.
    priorityqueue<int> c;
    for (int i = -5; i < -1; i++) {
        c.enqueue(i , i);
        c.enqueue(i + 100, i);  // has same priority but different value.
    }

    // doing peek multiple times.
    int value, priority;
    c.begin();
    EXPECT_EQ(c.peek(), -5);
    EXPECT_EQ(c.next(value, priority), true);
    EXPECT_EQ(value, -5);
    EXPECT_EQ(priority, -5);

    EXPECT_EQ(c.peek(), -5);
    EXPECT_EQ(c.peek(), -5);
    EXPECT_EQ(c.next(value, priority), true);  // should still be true.
    EXPECT_EQ(value, -5 + 100);
    EXPECT_EQ(priority, -5);
}

// testing for peek with char.
TEST(priorityqueue, peekChar) {
    // creating an empty queue.
    priorityqueue<char> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue('m' + i , i);
    }
    // looking at the min node.
    EXPECT_EQ(a.peek(), 'm' + -2);
    
    // testing peeking using dequeue.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.peek(), 'm' + i);
        a.dequeue();
    }

    // testing after all nodes removed.
    EXPECT_EQ(a.peek(), char{});

    // checking with duplicates.
    priorityqueue<char> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue('m' + i , i);
        b.enqueue('m' + i + 9, i);  // has same priority but different value.
    }
    // looking at the min node.
    EXPECT_EQ(b.peek(), 'm' + -5);
    
    // testing peeking using dequeue.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.peek(), 'm' + i);
        b.dequeue();
        EXPECT_EQ(b.peek(), 'm' + i + 9);
        b.dequeue();
    }
}

// testing for peek with string.
TEST(priorityqueue, peekString) {
    // creating an empty queue.
    priorityqueue<string> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue( "My num: " + to_string(i) , i);
    }
    // looking at the min node.
    EXPECT_EQ(a.peek(), "My num: " + to_string(-2));
    
    // testing peeking using dequeue.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.peek(), "My num: " + to_string(i));
        a.dequeue();
    }

    // testing after all nodes removed.
    EXPECT_EQ(a.peek(), string{});

    // checking with duplicates.
    priorityqueue<string> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue( "My num: " + to_string(i) , i);
        b.enqueue( "My num: " + to_string(i + 9), i);  // has same priority but different value.
    }
    // looking at the min node.
    EXPECT_EQ(b.peek(), "My num: " + to_string(-5));
    
    // testing peeking using dequeue.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.peek(), "My num: " + to_string(i));
        b.dequeue();
        EXPECT_EQ(b.peek(), "My num: " + to_string(i + 9));
        b.dequeue();
    }
}

// testing for peek with double.
TEST(priorityqueue, peekDouble) {
    // creating an empty queue.
    priorityqueue<double> a;
    // filling it up.
    for (int i = -2; i < 2; i++) {
        a.enqueue(i + 1.6789 , i);
    }
    // looking at the min node.
    EXPECT_EQ(a.peek(), 1.6789 - 2);
    
    // testing peeking using dequeue.
    for (int i = -2; i < 2; i++) {
        EXPECT_EQ(a.peek(), i + 1.6789);
        a.dequeue();
    }

    // testing after all nodes removed.
    EXPECT_EQ(a.peek(), double{});

    // checking with duplicates.
    priorityqueue<double> b;
    for (int i = -5; i < 10; i++) {
        b.enqueue(i + 1.6789 , i);
        b.enqueue(i + 1.6789 + 100, i);  // has same priority but different value.
    }
    // looking at the min node.
    EXPECT_EQ(b.peek(), 1.6789 - 5);
    
    // testing peeking using dequeue.
    for (int i = -5; i < 10; i++) {
        EXPECT_EQ(b.peek(), i + 1.6789);
        b.dequeue();
        EXPECT_EQ(b.peek(), i + 1.6789 + 100);
        b.dequeue();
    }
}