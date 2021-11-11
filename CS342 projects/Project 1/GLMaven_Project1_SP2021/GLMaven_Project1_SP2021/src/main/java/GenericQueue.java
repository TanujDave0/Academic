
// class to define the generic queue.
public class GenericQueue<T> extends GenericList<T> {
    private Node<T> tail; // field to store the tail of the queue.

    // constructor.
    public GenericQueue(T val) {
        setLength(1); // setting the length.
        setHead(new Node<T>(val)); // creating and assigning a new head
        tail = getHead(); // and tail.
    }

    // adds the value 'add' to the queue.
    public void add(T add) {
        // if the queue is empty.
        if (getLength() == 0) {
            // make a new head and tail.
            setHead(new Node<T>(add));
            tail = getHead();
        }
        else {
            // add to the end of the queue.
            tail.next = new Node<T>(add);
            tail = tail.next;
        }
        setLength(getLength() + 1); // setting the length.
    }

    // removing the tail of the queue.
    public T removeTail() {
        // if the list is empty returns null.
        if (getHead() == null || getLength() == 0) {
            return null;
        }

        // storing the data to be deleted.
        T ans = tail.data;
        Node<T> temp = getHead();
        while (temp.next != tail && temp.next != null) {
            temp = temp.next;
        }

        tail = temp;
        // if there is just one element.
        if (tail.next != null) {
            tail.next = null;
        } else {
            setHead(null);
        }

        setLength(getLength() - 1); // setting the length.

        return ans;
    }

    // enqueuing 'data' to the end of the queue.
    public void enqueue(T data) {
        add(data);
    }

    // removing and returning the next-in-line element.
    public T dequeue() {
        return delete();
    }
}