import java.util.Iterator;

// class to implement the Iterator for the GenericList.
public class GLLIterator<T> implements Iterator<T> {
    private GenericList<T>.Node<T> curr; // stores the current head.

    // constructor that initialises curr to the head.
    public GLLIterator(GenericList<T> list) {
        curr = list.getHead();
    }

    // returns boolean to check if there is a next value.
    public boolean hasNext() {
        return curr != null;
    }

    // returns the current value and advances curr.
    public T next() {
        T ans = curr.data;
        curr = curr.next;

        return ans;
    }
}