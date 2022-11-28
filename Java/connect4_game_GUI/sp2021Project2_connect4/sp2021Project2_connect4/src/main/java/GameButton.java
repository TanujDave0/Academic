import javafx.scene.control.*;
import javafx.geometry.*;
import javafx.scene.text.*; 
import javafx.scene.paint.Color;
import javafx.scene.layout.*;
import java.util.ArrayList;

public class GameButton extends Button {
    public int player;

    public GameButton(Background bg) {
        this.setPrefSize(50,50);
        this.setBackground(bg);
        player = -1;
    }

    public void pressed(Background bg, Background bg2, int player) {
        if (player == 1) {
            this.setBackground(bg);
        }else {
            this.setBackground(bg2);
        }
        this.setDisable(true);
        this.player = player;
    }

    public void unpress(Background bg) {
        this.setBackground(bg);
        this.setDisable(false);
        this.player = -1;
    }

    public void changeTheme(Background bt1, Background bt2) {
        if (this.player == 1) {
            this.setBackground(bt1);
        } else if (this.player == 2) {
            this.setBackground(bt2);
        }
    }
}