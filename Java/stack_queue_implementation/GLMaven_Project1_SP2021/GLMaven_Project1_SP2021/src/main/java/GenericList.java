import java.util.ArrayList;
import java.util.ListIterator;
import java.util.Iterator;

// class to implement Linked List.
abstract class GenericList<T> implements Iterable<T> {

    // class to define each node of the linked list.
    public class Node<T> {
        public T data;
        public Node<T> next;
        public Node<T> prev;

        // sets data equal to val
        public Node(T val) {
            this.data = val;
            this.next = null;
        }
    }

    // field storig the head of the list.
    private Node<T> head;
    // field storing the length/size of the list.
    private int length;

    // pritns the list.
    public void print() {
        // if the list is empty.
        if (length == 0 || head == null) {
            System.out.println("Empty list");
            return;
        }

        Node<T> temp = head;
        // iterating over each element and printing it.
        for (int i = 0; i < length; i++) {
            System.out.println(temp.data);
            temp = temp.next;
        }
    }

    public abstract void add(T add);

    // deletes the first entry in the list and returns it.
    public T delete() {
        if (head == null) {
            return null;
        }

        T ans = head.data;  // ans stored the value of the current head.
        head = head.next;  // head now points to the next value, thus first one deleted.

        length -= 1;
        return ans;  // return the original head.
    }

    // stores and returns the list in an ArrayList and deletes the list.
    public ArrayList<T> dumpList() {
        // if the list is empty.
        if (head == null) {
            return null;
        }

        // make and store the list in a ArrayList.
        ArrayList<T> ans = new ArrayList<T>(length);
        for (int i = 0; i < length; i++) {
            ans.add(head.data);
            this.head = this.head.next;
        }

        length = 0;
        return ans; // return the ArrayList.
    }

    // returns the entry at position 'index'.
    public T get(int index) {
        if (head == null || index >= length) {
            return null;
        }

        T ans = null;
        Node<T> temp = head;
        for (int i = 0; i < length; i++) {
            if (i == index) {
                ans = temp.data;
            }
            temp = temp.next;
        }

        return ans;
    }

    // sets the value of 'index' element to 'element' and returns the original value stored.
    public T set(int index, T element) {
        if (index >= length || head == null) {
            return null;
        }

        T ans = null;
        Node<T> temp = head;
        for (int i = 0; i < length; i++) {
            if (index == i) {
                ans = temp.data;
                temp.data = element;
            }
            temp = temp.next;
        }

        return ans;
    }

    // returns the head of the list.
    public Node<T> getHead() {
        return head;
    }

    // set the head of list to 'h'.
    public void setHead(Node<T> h) {
        this.head = h;
    }

    // returns the length of the list.
    public int getLength() {
        return length;
    }

    // setting a new length of the list.
    public void setLength(int len) {
        // checking if invalid length entered.
        if (len < 0) {
            System.out.println("Please enter a size that is non negative");
            return;
        }
        this.length = len;
    }

    // returns an iterator instance.
    public Iterator<T> iterator() {
        return new GLLIterator<T>(this);
    }
   
    // returns a list iterator instance.
    public ListIterator<T> listIterator(int index) {
        return new GLListIterator<T>(this, index);
    }
    
    // returns an iterator which moves in descending order.
    public Iterator<T> descendingIterator() {
        return new ReverseGLLIterator<T>(this);
    }
}