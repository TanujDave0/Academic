import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.jupiter.api.Test;

import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;

import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.ValueSource;

import javafx.application.Application;

import javafx.scene.control.*;
import javafx.geometry.*;
import javafx.scene.text.*; 
import javafx.scene.paint.Color;
import javafx.scene.layout.*;
import java.util.ArrayList;
import java.util.Stack;

import javafx.event.EventHandler;
import javafx.event.ActionEvent;

import javafx.stage.Stage;
import javafx.application.Platform;
import javafx.scene.*;
import javafx.scene.image.Image;

class MyTest {
    static GameLogic test;
    static Background bg1;
    static Background ac1;

	@BeforeEach
    void init() {
        Background bg1 = new Background(new BackgroundFill(Color.WHITESMOKE, CornerRadii.EMPTY, Insets.EMPTY));
        Background ac1 = new Background(new BackgroundFill(Color.RED, CornerRadii.EMPTY, Insets.EMPTY));
        test = new GameLogic();
    }

    @Test
    void constructorTest() {
        assertEquals(1, test.theme, "Theme wrongly initialised");
        assertEquals(1, test.player, "Player wrongly initialised");
        assertEquals(0, test.size(), "Stack wrongly initialised");
    }

    @Test
    void changeThemeTest() {
        test.changeTheme(2);
        assertEquals(2, test.theme, "Theme not chagned correctly");
    }

    @Test
    void changeThemeTest2() {
        test.changeTheme(9999);
        assertEquals(9999, test.theme, "Theme not changed correctly");
    }

    @Test
    void pressedNonwinningTest() {
        com.sun.javafx.application.PlatformImpl.startup(() -> {});
        ArrayList<ArrayList<GameButton>> buttons = new ArrayList<>();

        for (int i = 0; i < 6; i++) {
            buttons.add(new ArrayList<GameButton>());
            for(int j = 0; j < 7; j++) {
                buttons.get(i).add(new GameButton(bg1));
            }
        }

        int player = 1;
        ArrayList<Integer> list = new ArrayList<>();

        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 3; j++) {
                buttons.get(i).get(j).pressed(bg1, ac1, i);
                test.pressed(buttons, i, j);
                if (player == 1) {
                    player++;
                } else {
                    player--;
                }
                list.add(i*7+j);
                assertEquals(player, test.player, "Player incorrectly changed");
            }
        }

        Stack<Integer> stack = test.previousMoves();

        assertEquals(list.size(), stack.size(), "Stack has the wrong size");

        for (int  i = 0; i < stack.size(); i++) {
            assertEquals(list.get(list.size()-i-1), stack.pop(), "Stack incorrectly populated");
        }
    }

    @Test
    void reverseTest() {
        com.sun.javafx.application.PlatformImpl.startup(() -> {});
        ArrayList<ArrayList<GameButton>> buttons = new ArrayList<>();
        assertEquals(-1, test.reverse(buttons), "stack shoudl be empty");

        for (int i = 0; i < 6; i++) {
            buttons.add(new ArrayList<GameButton>());
            for(int j = 0; j < 7; j++) {
                buttons.get(i).add(new GameButton(bg1));
            }
        }

        int player = 1;
        ArrayList<Integer> list = new ArrayList<>();
        Stack<Integer> stack = test.previousMoves();

        for(int i = 0; i < 2; i++){
            for (int j = 0; j < 3; j++) {
                buttons.get(i).get(j).pressed(bg1, ac1, i);
                test.pressed(buttons, i, j);
                list.add(i*7+j);
            }
        }

        for (int  i = 0; i < stack.size(); i++) {
            assertEquals(list.get(list.size()-i-1), test.reverse(buttons), "Stack incorrectly populated");
            if (player == 1) {
                player++;
            } else {
                player--;
            }
            assertEquals(player, test.player, "Player incorrectly changed");
        }


    }
    // test wining conditions
    // collab pdf
    // info text

}
