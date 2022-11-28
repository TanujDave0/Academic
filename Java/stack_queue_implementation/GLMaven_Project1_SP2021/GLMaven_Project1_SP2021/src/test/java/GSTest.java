import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.ListIterator;
import java.util.Iterator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;


// class to test the stack and its methods.
class GenericStackTest {
    static GenericStack<Integer> stack;
    static ArrayList<Integer> test;

    @BeforeEach
    void init() {
        // initialising stack and a array to test if the values are correct.
        stack = new GenericStack<Integer>(0);
        test = new ArrayList<Integer>();
        test.add(0);

        for (int i = 1; i < 6; i++) {
            test.add(i);
            stack.add(i);
        }
    }

    // testnig the constructor.
    @Test
    void constructorTest() {
        GenericStack<Integer> stack = new GenericStack<>(1);

        // checking if the 1 was pushed correctly and length was altered.
        assertEquals(1, stack.getLength(), "Constructor fault: wrong length");
        assertEquals(1, stack.get(0), "Constuctor fault: wrong element");
    }

    // testing add and get.
    @Test
    void addGetTest() {
        for (int i = 0; i < 6; i++) {
            // added already in the constructor and testing both get.
            assertEquals(test.get(5 - i), stack.get(i), "Wrong get() or add()");
        }
    }

    // testing the set method.
    @Test
    void setGetTest() {
        // setting all the nodes to different values.
        for (int i = 0; i < 6; i++) {
            test.set(5 - i, i+999);
            stack.set(i, i+999);
        }

        // testing if all the values are changed correctly.
        for (int i = 0; i < 6; i++) {
            assertEquals(test.get(5 - i), stack.get(i), "Wrong get() or add()");
        }
    }

    // trying to add to an empty stack.
    @Test
    void pushTestEmpty() {
        // deleting all the nodes in the list.
        stack.dumpList();
        stack.push(10);

        assertEquals(10, stack.get(0), "Wrongly added to empty list");
        assertEquals(1, stack.getLength(), "Wrong size of empty list after addition");
    }
    
    // testing the stack with string values.
    @Test
    void pushTest() {
        // creating a differnet stack to test the push functions with strings.
        GenericStack<String> stack2 = new GenericStack<>("A");
        ArrayList<String> list = new ArrayList<>();

        list.add("A");
        for (int i = 0; i < 10; i++) {
            list.add("A" + i);
            stack2.add("A" + i);
        }

        // checking if all the values are correct.
        for (int i = 0; i < 11; i++) {
            assertEquals(list.get(10 - i), stack2.get(i), "String push faulty");
        }
    }

    // testing the pop method.
    @Test
    void popTest() {
        // removing the first 2 values from stack and
        // last two values from the array.
        test.remove(5);
        test.remove(4);
        stack.pop();
        stack.pop();

        for (int i = 0; i < 4; ++i) {
            assertEquals(test.get(3 - i), stack.get(i));
        }
    }

    // testing the pop function on an empty stack.
    @Test
    void popTestEmpty() {
        stack.dumpList();
        stack.pop();

        assertEquals(0, stack.getLength(), "Wrong size of empty list after pop");
    }

    // testing pop in a stack with only one element.
    @Test
    void popTestOneElement() {
        stack.dumpList();
        stack.add(10);
        stack.pop();

        assertEquals(0, stack.getLength(), "Wrong size of empty list after pop");
    }

    // testing the dump function.
    @Test
    void dumpListTest() {
        stack.dumpList();
        
        // checking if the length is changed correctly.
        assertEquals(0, stack.getLength(), "Wrong size");
        assertNull(stack.getHead()); // checking if the head is null (empty).
    }

    // testing the get and setHead() functions.
    @Test
    void getSetHeadTest() {
        // creating a stack instance to make a node instance.
        GenericStack<Integer> temp = new GenericStack<>(29);
        GenericStack<Integer>.Node<Integer> node = temp.new Node<Integer>(75);
        
        // setting the node created as the head and checking if altered correctly.
        stack.setHead(node);
        assertEquals(node, stack.getHead(), "Heads not equal");
    }

    // testing the set and get length function.
    @Test
    void setGetLengthTest() {
        stack.setLength(5);

        // testing the length.
        assertEquals(5, stack.getLength(), "Length incorrect");

        // testing if incorrect length is ignored.
        stack.setLength(-1);
        assertNotEquals(-1, stack.getLength(), "wrong length");
    }

    // testing the iterator.
    @Test
    void iteratorTest() {
        int i = 5;
        // using a for each loop.
        for (Integer num : stack) {
            assertEquals(i--, num, "Value different");
        }

        // setting all the values to 0 to test forEach().
        for (int j = 0; j < stack.getLength(); j++) {
            stack.set(j, 0);
        }

        // testing if forEach() works.
        stack.forEach((num) -> assertEquals(0, num, "Wrong elements"));
    }

    // tesing the list iterator.
    @Test
    void listIteratorTest() {
        // creating a listiterator instance.
        ListIterator<Integer> iterator = stack.listIterator(0);

        int i = 5;
        // checking the hasnext and next.
        while (iterator.hasNext()) {
            assertEquals(i--, iterator.next());
        }

        // creating a different instance of list iterator.
        ListIterator<Integer> iterator2 = stack.listIterator(5);
        i = 0;
        // checking hasPrevious and preivous.
        while (iterator2.hasPrevious()) {
            assertEquals(i++, iterator2.previous());
        }
    }

    // testing the listiterator.
    @Test
    void listIteratorTest2() {
        ListIterator<Integer> iterator = stack.listIterator(0);

        // testing nextIndex.
        for (int i = 1; i < stack.getLength(); i++) {
            assertEquals(i, iterator.nextIndex(), "Wrong index");
            iterator.next();
        }
    }

    @Test
    void listIteratorTest3() {
        // creating a list iterator instance from middle.
        ListIterator<Integer> iterator2 = stack.listIterator(5);

        // testing nextIndex from a middle index.
        for (int i = 6; i < stack.getLength() - 1; i++) {
            assertEquals(i, iterator2.nextIndex(), "Wrong index");
            iterator2.next();
        }
    }

    // testing list iterator's previous Index from a middle index.
    @Test
    void listIteratorTest4() {        
        ListIterator<Integer> iterator3 = stack.listIterator(5);

        for (int i = 4; i > 0; i--) {
            assertEquals(i, iterator3.previousIndex(), "Wrong index");
            iterator3.previous();
        }
    }

    // testing the descending iterator.
    @Test
    void descendingIteratorTest() {
        // creating an instance of descending iterator.
        Iterator<Integer> iterator = stack.descendingIterator();

        int i = 0;
        while (iterator.hasNext()) {
            assertEquals(i++, iterator.next(), "Wrong descending iterator");
        }
    }

    // testing descending iterator with many values.
    @Test
    void descendingIteratorTest2() {
        GenericStack<Integer> stack2 = new GenericStack<>(59);
        ArrayList<Integer> test2 = new ArrayList<>();
        test2.add(59);

        Iterator<Integer> iterator = stack2.descendingIterator();

        for (int i = 0; i < 10000; i++) {
            test2.add(i);
            stack2.add(i);
        }

        int i = 0;
        while (iterator.hasNext()) {
            assertEquals(test2.get(i++), iterator.next(), "Wrong descending iterator");
        }
    }

    // testing remove tail mthod.
    @Test
    void removeTailTest() {
        // checking if remove tail removes and returns tail correctly.
        assertEquals(0, stack.removeTail(), "Tail wrongly removed");
        assertEquals(5, stack.getLength(), "Tails removed wrong size");
    }

    // testing the remove tail on empty stack.
    @Test
    void removeTailTest2() {
        // trying to remove the tail of an empty stack.
        stack.dumpList();
        assertNull(stack.removeTail());
    }

    // testing remove tail where tail is the head.
    @Test
    void removeTailTest3() {
        // removing a tail which is head.
        stack.dumpList();
        stack.add(1);

        assertEquals(1, stack.removeTail(), "Tail wrongly removed");
        assertEquals(0, stack.getLength(), "Tails removed wrong size");
    }
}