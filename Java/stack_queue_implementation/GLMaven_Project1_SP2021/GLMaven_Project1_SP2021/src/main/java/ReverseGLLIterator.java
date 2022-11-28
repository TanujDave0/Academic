import java.util.Iterator;

// class to implement the reverse Iterator for the GenericList.
public class ReverseGLLIterator<T> implements Iterator<T> {
    private GenericList<T>.Node<T> curr;

    // constructor that initialises curr to the tail.
    public ReverseGLLIterator(GenericList<T> list) {
        GenericList<T>.Node<T> prev = null;
        GenericList<T>.Node<T> temp = list.getHead();

        while (temp != null) {
            curr = temp;
            curr.prev = prev;
            prev = curr;
            temp = temp.next;
        }
    }

    // returns boolean to check if there is a next value.
    public boolean hasNext() {
        return curr != null;
    }

    // returns the current value and advances curr.
    public T next() {
        T ans = curr.data;
        curr = curr.prev;

        return ans;
    }
}