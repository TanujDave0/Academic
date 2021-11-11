import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;
import java.util.ListIterator;
import java.util.Iterator;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

// class to the queue and its methods.
class GenericQueueTest {
    static GenericQueue<Integer> queue;
    static ArrayList<Integer> test;

    @BeforeEach
    void init() {
        // initialising queue and a array to test if the values are correct.
        queue = new GenericQueue<Integer>(0);
        test = new ArrayList<Integer>();
        test.add(0);

        for (int i = 1; i < 6; i++) {
            test.add(i);
            queue.add(i);
        }
    }

    // testnig the constructor.
    @Test
    void constructorTest() {
        GenericQueue<Integer> queue = new GenericQueue<>(1);

        assertEquals(1, queue.getLength(), "Constructor fault: wrong length");
        assertEquals(1, queue.get(0), "Constuctor fault: wrong element");
    }

    // testing add and get.
    @Test
    void addGetTest() {
        for (int i = 0; i < 6; i++) {
            assertEquals(test.get(i), queue.get(i), "Wrong get() or add()");
        }
    }

    // testing the set method.
    @Test
    void setGetTest() {
        for (int i = 0; i < 6; i++) {
            test.set(i, i+999);
            queue.set(i, i+999);
        }

        for (int i = 0; i < 6; i++) {
            assertEquals(test.get(i), queue.get(i), "Wrong get() or add()");
        }
    }

    // trying to add to an empty queue.
    @Test
    void enqueueTestEmpty() {
        queue.dumpList();
        queue.enqueue(10);

        assertEquals(10, queue.get(0), "Wrongly added to empty list");
        assertEquals(1, queue.getLength(), "Wrong size of empty list after addition");
    }
    
    // testing the queue with string values
    @Test
    void enqueueTest() {
        GenericQueue<String> queue2 = new GenericQueue<>("A");
        ArrayList<String> list = new ArrayList<>();
        list.add("A");
        for (int i = 0; i < 10; i++) {
            list.add("A"+i);
            queue2.add("A"+i);
        }

        for (int i = 0; i < 10; i++) {
            assertEquals(list.get(i), queue2.get(i), "String enqueue faulty");
        }
    }

    // testing the dequeue method.
    @Test
    void dequeueTest() {
        queue.dequeue();
        queue.dequeue();
        test.remove(0);
        test.remove(0);

        for (int i = 0; i < queue.getLength(); ++i) {
            assertEquals(test.get(i), queue.get(i));
        }
    }

    // testing the dequeue function on an empty queue.
    @Test
    void dequeueTestEmpty() {
        queue.dumpList();
        queue.dequeue();

        assertEquals(0, queue.getLength(), "Wrong size of empty list after dequeue");
    }

    // testing dequeue in a queue with only one element.
    @Test
    void dequeueTestOneElement() {
        queue.dumpList();
        queue.add(10);
        queue.dequeue();

        assertEquals(0, queue.getLength(), "Wrong size of empty list after dequeue");
    }

    // testing the dump function.
    @Test
    void dumpListTest() {
        queue.dumpList();
        
        // checking if the length is changed correctly.
        assertEquals(0, queue.getLength(), "Wrong size");
        assertNull(queue.getHead());
    }

    // testing the get and setHead() functions.
    @Test
    void getSetHeadTest() {
        GenericQueue<Integer> temp = new GenericQueue<>(29);
        GenericQueue<Integer>.Node<Integer> node = temp.new Node<Integer>(75);
        
        // setting the node created as the head and checking if altered correctly.
        queue.setHead(node);
        assertEquals(node, queue.getHead(), "Heads not equal");
    }

    // testing the set and get length function.
    @Test
    void setGetLengthTest() {
        queue.setLength(5);

        // testing the length.
        assertEquals(5, queue.getLength(), "Length incorrect");

        // testing if incorrect length is ignored.
        queue.setLength(-1);
        assertNotEquals(-1, queue.getLength(), "wrong length");
    }

    // testing the iterator.
    @Test
    void iteratorTest() {
        int i = 0;

        // using a for each loop.
        for (Integer num : queue) {
            assertEquals(i++, num, "Value different");
        }

        // setting all the values to 0 to test forEach().
        for (int j = 0; j < queue.getLength(); j++) {
            queue.set(j, 0);
        }

        // testing if forEach() works.
        queue.forEach((num) -> assertEquals(0, num, "Wrong elements"));
    }

    // tesing the list iterator.
    @Test
    void listIteratorTest() {
        // creating a listiterator instance.
        ListIterator<Integer> iterator = queue.listIterator(0);

        int i = 0;
        // checking the hasnext and next.
        while (iterator.hasNext()) {
            assertEquals(i++, iterator.next());
        }

        ListIterator<Integer> iterator2 = queue.listIterator(5);
        i = 5;
        // checking hasPrevious and preivous.
        while (iterator2.hasNext()) {
            assertEquals(i--, iterator2.previous());
        }
    }

    // testing the listiterator.
    @Test
    void listIteratorTest2() {
        ListIterator<Integer> iterator = queue.listIterator(0);

        for (int i = 1; i < queue.getLength(); i++) {
            assertEquals(i, iterator.nextIndex(), "Wrong index");
            iterator.next();
        }
    }

    @Test
    void listIteratorTest3() {
        // creating a list iterator instance from middle.
        ListIterator<Integer> iterator2 = queue.listIterator(5);

        for (int i = 6; i < queue.getLength() - 1; i++) {
            assertEquals(i, iterator2.nextIndex(), "Wrong index");
            iterator2.next();
        }
    }

    // testing list iterator's previous Index from a middle index.
    @Test
    void listIteratorTest4() {        
        ListIterator<Integer> iterator3 = queue.listIterator(5);

        for (int i = 4; i > 0; i--) {
            assertEquals(i, iterator3.previousIndex(), "Wrong index");
            iterator3.previous();
        }
    }

    // testing the descending iterator.
    @Test
    void descendingIteratorTest() {
        // creating an instance of descending iterator.
        Iterator<Integer> iterator = queue.descendingIterator();

        int i = queue.getLength() - 1;
        while (iterator.hasNext()) {
            assertEquals(i--, iterator.next(), "Wrong descending iterator");
        }
    }

    // testing descending iterator with many values.
    @Test
    void descendingIteratorTest2() {
        GenericQueue<Integer> queue2 = new GenericQueue<>(59);
        ArrayList<Integer> test2 = new ArrayList<>();
        test2.add(59);

        Iterator<Integer> iterator = queue2.descendingIterator();

        for (int i = 0; i < 10000; i++) {
            test2.add(i);
            queue2.add(i);
        }

        int i = 0;
        while (iterator.hasNext()) {
            assertEquals(test2.get(i++), iterator.next(), "Wrong descending iterator");
        }
    }

    // testing remove tail mthod.
    @Test
    void removeTailTest() {
        assertEquals(5, queue.removeTail(), "Tail wrongly removed");
        assertEquals(5, queue.getLength(), "Tails removed wrong size");
    }

    // testing the remove tail on empty queue.
    @Test
    void removeTailTest2() {
        // trying to remove the tail of an empty queue.
        queue.dumpList();
        assertNull(queue.removeTail());
    }

    // testing remove tail where tail is the head.
    @Test
    void removeTailTest3() {
        // removing a tail which is head.
        queue.dumpList();
        queue.add(1);

        assertEquals(1, queue.removeTail(), "Tail wrongly removed");
        assertEquals(0, queue.getLength(), "Tails removed wrong size");
    }
}