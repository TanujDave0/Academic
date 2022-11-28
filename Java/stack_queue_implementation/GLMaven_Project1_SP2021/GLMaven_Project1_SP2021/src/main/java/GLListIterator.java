import java.util.ListIterator;

// class to implement the list iterator for generic linked-list.
public class GLListIterator<T> implements ListIterator<T> {
    // fields to hold to index of and the current node.
    private int index;
    private GenericList<T>.Node<T> curr;

    public void add(T e) {}
    public void set(T e) {}
    public void remove() {}

    // constructor.
    public GLListIterator(GenericList<T> list, int ind) {
        index = ind; // storing the current index.

        GenericList<T>.Node<T> prev = null;
        GenericList<T>.Node<T> cur;
        GenericList<T>.Node<T> temp = list.getHead();

        // looping and attaching all the nodes to their previous nodes.
        while (temp != null) {
            // if we are on the index where we want to be.
            if (ind == 0) {
                curr = temp;
            }
            cur = temp;
            // attaching element to its previous one.
            cur.prev = prev;
            prev = cur;
            temp = temp.next;
            ind--;
        }
    }

    // if there is a next value in the list returns true.
    public boolean hasNext() {
        return curr != null;
    }

    // if there is a preious value returns true.
    public boolean hasPrevious() {
        return curr != null;
    }

    // returns the current value and increments the current.
    public T next() {
        T ans = curr.data;
        curr = curr.next;
        index++;

        return ans;
    }

    // returns the index of next value.
    public int nextIndex() {
        return index+1;
    }

    // returns the previous element and decrements the index.
    public T previous() {
        T ans = curr.data;
        curr = curr.prev;
        index--;

        return ans;
    }

    // returns the previous elements index.
    public int previousIndex() {
        return index-1;
    }

}