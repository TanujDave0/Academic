
// class to define a generic stack.
public class GenericStack<T> extends GenericList<T> {
    // field pointing to the tail of the stack.
    Node<T> tail;

    // constructor.
    public GenericStack(T val) {
        setLength(1); // setting the length to 1.
        setHead(new Node<T>(val)); // adding the new head and tail.
        tail = getHead();
    }

    // add method to add a new value/node.
    public void add(T add) {
        // if the stack is empty
        if (getLength() == 0) {
            setHead(new Node<T>(add));
            tail = getHead();
        } else {  // if the stack is filled.
            Node<T> temp = new Node<T>(add);
            temp.next = getHead();
            setHead(temp);
        }

        setLength(getLength()+1); // incrementing the stack.
    }

    // pushing a new value onto the stack.
    public void push(T data) {
        add(data);
    }

    // removing the topmost value.
    public T pop() {
        return delete();
    }

    // removing from the tail of the stack and returning the data.
    public T removeTail() {
        // if the stack is empty.
        if (getHead() == null || getLength() == 0) {
            return null;
        }

        // taking the data to be removed.
        T ans = tail.data;
        Node<T> temp = getHead();
        // looping to just beofre the tail.
        while (temp.next != tail && temp.next != null) {
            temp = temp.next;
        }

        tail = temp;
        // if the tail is head (only one element).
        if (tail.next != null) {
            tail.next = null;
        } else {
            setHead(null);
        }

        setLength(getLength() - 1);// decreasing the length.

        return ans;  // returning the tail removed.
    }
}