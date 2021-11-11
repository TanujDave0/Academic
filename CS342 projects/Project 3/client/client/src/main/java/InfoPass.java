import java.io.Serializable;
import java.util.*;

class InfoPass implements Serializable {
    private static final long serialVersionUID = 1L;

    String message;

    ArrayList<String> Categories;
    int catNum;
    ArrayList<Integer> catTries;
    ArrayList<Boolean> catGuess;

    // String category;
    String word;
    int guesses;

    String letter;
    int pos;
    int size;
    boolean exist;

    boolean win;
    boolean lose;
}