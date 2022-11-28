import javafx.event.EventHandler;

import java.util.*;

import javafx.event.ActionEvent;

public class GameLogic {
    public int player;
    private Stack<Integer> prevMoves;
    public int theme;

    public GameLogic() {
        theme = 1;
        player = 1;
        prevMoves = new Stack<>();
    }

    public Stack<Integer> previousMoves() {
        return prevMoves;
    }

    public void changeTheme(int to) {
        this.theme = to;
    }

    public int reverse(ArrayList<ArrayList<GameButton>> buttons) {
        if (prevMoves.empty()) {
            return -1;
        }
        int pos = prevMoves.pop();
        if (player == 1) {
            player++;
        } else {
            player--;
        }
        return pos;
    }

    public int size() {
        return prevMoves.size();
    }

    public boolean pressed(ArrayList<ArrayList<GameButton>> buttons, int i, int j) {
        if (player == 1) {
            player++;
        } else {
            player--;
        }
        
        prevMoves.push(i*7 + j);

        return checkWinning(buttons);
    }

    public boolean checkValidity(ArrayList<ArrayList<GameButton>> buttons, int i, int j) {
        if (i > 4) {
            return true;
        }
        if (buttons.get(i+1).get(j).isDisabled()) {
            return true;
        } else {
            return false;
        }
    }  

    public boolean checkWinning(ArrayList<ArrayList<GameButton>> buttons) {
        // column
        for (int i = 0; i < 7; i++) { // for row
            int prev = -999;
            int streak = 1;
            for (int j = 0; j < 6; j++) { // for column
                if (prev != buttons.get(j).get(i).player) {
                    prev = buttons.get(j).get(i).player;
                    streak = 1;
                } else if (prev != -1) {
                    streak++;
                }
                if (streak == 4) {
                    System.out.println("column at " + j + i);
                    return true;
                }
                
            }
        }

        // row
        for (int i = 0; i < 6; i++) {
            int prev = -999;
            int streak = 1;
            for(int j = 0; j < 7; j++) {
                if (prev != buttons.get(i).get(j).player) {
                    prev = buttons.get(i).get(j).player;
                    streak = 1;
                } else if (prev != -1) {
                    streak++;
                }
                if (streak == 4) {
                    System.out.println("row at " + i + j);
                    return true;
                }
            }
        }

        // diagonal right
        for (int i = 0; i < 6; i++) {
            for(int j = 0; j < 7; j++) {
                if (diagonal(buttons, i, j)) {
                    System.out.println("diagonal at " + i + j);
                    return true;
                }
            }
        }

        return false;
    }

    private boolean diagonal(ArrayList<ArrayList<GameButton>> buttons, int a, int b) {
        int prev = -999;
        int streak = 1;
        // right diagonal
        int i = a;
        int j = b;
        while (i < 6 && j < 7) {
            if (prev != buttons.get(i).get(j).player) {
                prev = buttons.get(i).get(j).player;
                streak = 1;
            } else if (prev != -1) {
                streak++;
            }
            if (streak == 4) {
                System.out.println("right diagonal at");
                return true;
            }
            i++;
            j++;
        }
        streak = 1;
        prev = -999;

        i = a;
        j = b;        
        // left diagonal
        while (i < 6 && j > 0) {
            if (prev != buttons.get(i).get(j).player) {
                prev = buttons.get(i).get(j).player;
                streak = 1;
            } else if (prev != -1) {
                streak++;
            }
            if (streak == 4) {
                System.out.println("left diagonal");
                return true;
            }
            i++;
            j--;
        }

        return false;
    }
}