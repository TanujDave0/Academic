import java.util.*;

public class GameLogic {
    public InfoPass curr;
    
    ArrayList<ArrayList<String>> dict;

    String word;

    GameLogic() {
        curr = new InfoPass();
        dict = new ArrayList<>();

        dict.add(new ArrayList<String>()); // mammals
        dict.add(new ArrayList<String>()); // reptiles
        dict.add(new ArrayList<String>());  // birds

        dict.get(0).add("elephant");
        dict.get(0).add("human");
        dict.get(0).add("dog");

        dict.get(1).add("crocodile");
        dict.get(1).add("lizard");
        dict.get(1).add("snake");

        dict.get(2).add("sparrow");
        dict.get(2).add("eagle");
        dict.get(2).add("canary");

        curr.Categories = new ArrayList<>();
        curr.Categories.add("Mamals");
        curr.Categories.add("Reptiles");
        curr.Categories.add("Birds");

        curr.catTries = new ArrayList<>();
        curr.catTries.add(3);
        curr.catTries.add(3);
        curr.catTries.add(3);

        curr.guesses = 6;
        curr.size = 0;

        curr.win = false;
        curr.lose = false;

        curr.catGuess = new ArrayList<>();
        curr.catGuess.add(false);
        curr.catGuess.add(false);
        curr.catGuess.add(false);

        curr.catNum = 0;

        curr.word = new String("");
    }

    public boolean pickCat(int cat) {
        curr.catNum = cat;

        return generateWord();
    }

    public boolean generateWord() {
        int cum = curr.catNum;
        
        if (lost()) {
            return false;
        }

        word = dict.get(cum - 1).get(curr.catTries.get(cum-1)-1);
        curr.catTries.set(cum-1, curr.catTries.get(cum-1)-1);

        curr.guesses = 6;
        curr.win = false;
        curr.lose = false;
        curr.size = word.length();

        for (int i = 0; i < word.length(); i++) {
            curr.word += "_";
        }

        return true;
    }

    public boolean guess(String letter) {
        for (int i = 0; i < word.length(); i++) {
            if (letter.charAt(0) == word.charAt(i)) {
                curr.exist = true;
                curr.message = "Good guess, the letter " + letter + " is in the word at the position " + String.valueOf(i+1) + "!";
                curr.pos = i;
                curr.word = curr.word.substring(0, i) + letter.charAt(0) + curr.word.substring(i+1);               

                if (word == curr.word) {
                    curr.catGuess.set(curr.catNum - 1, true);
                    curr.message = "You guess the word in one category! please select other";
                    reset();
                }

                if (win()) {
                    curr.message = "Congratulation! You have won";
                }
                
                return true;
            }
        }
    
        curr.guesses--;
        curr.message = "Sorry! The letter " + letter + " doesn't exist in the word, keep guessing.";

        if (curr.guesses == 0) {
            curr.catTries.set(curr.catNum - 1, curr.catTries.get(curr.catNum - 1) - 1);

            curr.message = "You have used all your 6 guesses, Please pick a category";
            if (lost()) {
                curr.message = "You have lost";
                return false;
            }

            reset();
        }

        curr.exist = false;
        return false;
    }

    public void reset() {
        curr.catNum = 0;
        curr.word = "";
        curr.guesses = 6;

        curr.letter = "";
        curr.lose = false;
        curr.pos = -1;
        curr.size = 0;
        curr.win = false;
    }

    public boolean lost() {
        for (int e: curr.catTries) {
            if (e == 0) {
                curr.win = false;
                curr.lose = true;
                return true;
            }
        }
        
        return false;
    }

    public boolean win() {
        for (boolean e: curr.catGuess) {
            if (!e) {
                return false;
            }
        }

        return true;
    }
}