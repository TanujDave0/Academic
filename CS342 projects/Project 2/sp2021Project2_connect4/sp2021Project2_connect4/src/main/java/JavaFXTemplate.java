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

public class JavaFXTemplate extends Application {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
        // original theme
        Background bg1 = new Background(new BackgroundFill(Color.WHITESMOKE, CornerRadii.EMPTY, Insets.EMPTY));
        Background ac1 = new Background(new BackgroundFill(Color.RED, CornerRadii.EMPTY, Insets.EMPTY));
        Background bt1 = new Background(new BackgroundFill(Color.YELLOW, new CornerRadii(500), Insets.EMPTY));
        Background bt2 = new Background(new BackgroundFill(Color.RED, new CornerRadii(500), Insets.EMPTY));
        Background ub1 = new Background(new BackgroundFill(Color.LIGHTGRAY, new CornerRadii(500), Insets.EMPTY));

        Background bg2 = new Background(new BackgroundFill(Color.BLACK, CornerRadii.EMPTY, Insets.EMPTY));
        Background ac2 = new Background(new BackgroundFill(Color.RED, CornerRadii.EMPTY, Insets.EMPTY));
        Background bt3 = new Background(new BackgroundFill(Color.GRAY, new CornerRadii(500), Insets.EMPTY));
        Background bt4 = new Background(new BackgroundFill(Color.RED, new CornerRadii(500), Insets.EMPTY));
        Background ub2 = new Background(new BackgroundFill(Color.LIGHTGRAY, new CornerRadii(500), Insets.EMPTY));

        Background bg3 = new Background(new BackgroundFill(Color.NAVY, CornerRadii.EMPTY, Insets.EMPTY));
        Background ac3 = new Background(new BackgroundFill(Color.CRIMSON, CornerRadii.EMPTY, Insets.EMPTY));
        Background bt5 = new Background(new BackgroundFill(Color.GOLDENROD, new CornerRadii(500), Insets.EMPTY));
        Background bt6 = new Background(new BackgroundFill(Color.CRIMSON, new CornerRadii(500), Insets.EMPTY));
        Background ub3 = new Background(new BackgroundFill(Color.LIGHTGRAY, new CornerRadii(500), Insets.EMPTY));

        int th = 1;

		// TODO Auto-generated method stub
		primaryStage.setTitle("Connect Four");

        //########################### WELCOME SCREEN ##################################
        Text msg = new Text();
        msg.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 50));
        msg.setText("Welcome to Connect Four");
        msg.setFill(Color.RED);

        Button play = new Button("Play!");
        VBox root = new VBox(msg, play);
        root.setAlignment(Pos.CENTER);

        root.setMargin(msg, new Insets(0,0,100,0));
        root.setMargin(play, new Insets(0,0,50,0));

        root.setBackground(bg1);
		Scene scene = new Scene(root, 700,700);

        //############################ GAME PLAY SCREEN #########################################
        // game play menu
        Menu gPM = new Menu("Game Play");
        MenuItem rev = new MenuItem("reverse move");
        gPM.getItems().add(rev);

        // Themes Menu
        Menu themes = new Menu("Themes");
        MenuItem oT = new MenuItem("original theme");
        MenuItem t1 = new MenuItem("theme one");
        MenuItem t2 = new MenuItem("theme two");
        themes.getItems().add(oT);
        themes.getItems().add(t1);
        themes.getItems().add(t2);

        // Options Menu
        Menu opt = new Menu("Options");
        MenuItem htp = new MenuItem("how to play");
        MenuItem ng = new MenuItem("new game");
        MenuItem ex = new MenuItem("exit");
        opt.getItems().add(htp);
        opt.getItems().add(ng);
        opt.getItems().add(ex);

        // menu bar
        MenuBar bar = new MenuBar();
        bar.getMenus().add(gPM);
        bar.getMenus().add(themes);
        bar.getMenus().add(opt);

        // Info 
        TextField turn = new TextField("Player 1's turn");
        turn.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 16.7));
        TextField moveInfo = new TextField("Player 1's turn");
        moveInfo.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 13.4));
        moveInfo.setMinWidth(420.00);
        moveInfo.setDisable(true);
        turn.setDisable(true);
        BackgroundFill bk2 = new BackgroundFill(Color.RED, new CornerRadii(10), Insets.EMPTY);
        moveInfo.setBackground(ac1);
        
        // info line
        HBox info = new HBox(10, turn, moveInfo);
        turn.setAlignment(Pos.CENTER);
        info.setPadding(new Insets(0,0,0,50));
        info.setBackground(bg1);

        // game board
        GridPane board = new GridPane();
        ArrayList<ArrayList<GameButton>> buttons = new ArrayList<>();

        for (int i = 0; i < 6; i++) {
            buttons.add(new ArrayList<GameButton>());
            for(int j = 0; j < 7; j++) {
                buttons.get(i).add(new GameButton(ub1));
            }
        }

        int k = 0;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                board.add(buttons.get(i).get(j), j, i);
            }
        }

        board.setHgap(10);
        board.setVgap(10);

        board.setAlignment(Pos.TOP_CENTER);
        board.setBackground(bg1);


        VBox test= new VBox(80,bar, info, board);
        test.setBackground(bg1);

        Scene gamePlay = new Scene(test,700, 700);

        //############################ Final Scene ########################################
        Text finalMsg = new Text();
        finalMsg.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 50));
        finalMsg.setFill(Color.RED);

        Button playAgain = new Button("Play Again");
        Button exit = new Button("Exit");
        VBox finalScreen = new VBox(finalMsg, playAgain, exit);
        finalScreen.setAlignment(Pos.CENTER);

        finalScreen.setMargin(finalMsg, new Insets(0,0,100,0));
        finalScreen.setMargin(playAgain, new Insets(0,0,50,0));

        finalScreen.setBackground(bg1);
		Scene finalScene = new Scene(finalScreen, 700,700);

        //############################### Info Screen #######################################
        TextField infoMsg = new TextField();
        infoMsg.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 50));
        infoMsg.setDisable(true);

        Button goBack = new Button("Return to Game");
        VBox infoScreen = new VBox(100, infoMsg, goBack);
        infoScreen.setAlignment(Pos.CENTER);

        infoScreen.setMargin(finalMsg, new Insets(0,0,100,0));
        infoScreen.setMargin(playAgain, new Insets(0,0,50,0));

        infoScreen.setBackground(bg1);
		Scene infoScene = new Scene(infoScreen, 700,700);

        //######################################## Game ######################################
        GameLogic game =  new GameLogic();

        for (int i = 0; i < 6; i++) {
            final int pos = i;
            for (int j = 0; j < 7; j++) {
                final int pos2 = j;
                buttons.get(i).get(j).setOnAction(e-> {
                    if (!game.checkValidity(buttons, pos, pos2)) {
                        moveInfo.setText("Player " + game.player + " moved to " + (pos+1) + ","
                        + (pos2 + 1) + " This is NOT a valid move. Player " + game.player +
                        " pick again.");
                    } else {
                        if (game.theme == 1) {
                            buttons.get(pos).get(pos2).pressed(bt1, bt2, game.player);
                        } else if (game.theme == 2) {
                            buttons.get(pos).get(pos2).pressed(bt3, bt4, game.player);
                        } else {
                            buttons.get(pos).get(pos2).pressed(bt5, bt6, game.player);
                        }
                        moveInfo.setText("Player " + game.player + " moved to " +
                                        (pos + 1) + "," + (pos2 + 1) + 
                                        " This is a valid move.");
                        // winning condtion
                        if (game.pressed(buttons, pos, pos2)) {
                            int won = 1;
                            if (game.player == 1) {
                                won = 2;
                            }
                            finalMsg.setText("Player " + won + " Won!");
                            primaryStage.setScene(finalScene);
                            // game screen resest
                            final int size = game.size();
                            for (int l = 0; l < size; l++) {
                                int p = game.reverse(buttons);
                                if (game.theme == 1) {
                                    buttons.get(p/7).get(p%7).unpress(ub1);
                                } else if (game.theme == 2) {
                                    buttons.get(p/7).get(p%7).unpress(ub2);
                                } else {
                                    buttons.get(p/7).get(p%7).unpress(ub3);
                                }
                            }
                            turn.setText("Player 1's turn");
                            moveInfo.setText("Player 1's turn");
                        }
                        // if tie
                        if (game.size() == 42) {
                            finalMsg.setText("It's a tie!!");
                            primaryStage.setScene(finalScene);
                            final int size = game.size();
                            for (int l = 0; l < size; l++) {
                                int p = game.reverse(buttons);
                                if (game.theme == 1) {
                                    buttons.get(p/7).get(p%7).unpress(ub1);
                                } else if (game.theme == 2) {
                                    buttons.get(p/7).get(p%7).unpress(ub2);
                                } else {
                                    buttons.get(p/7).get(p%7).unpress(ub3);
                                }
                            }
                            turn.setText("Player 1's turn");
                            moveInfo.setText("Player 1's turn");
                        }
                        turn.setText("Player " + game.player + "'s turn");
                    }
                });
            }
        }

        // reverse move
        rev.setOnAction(e-> {
            final int pos = game.reverse(buttons);
            if (pos == -1) {
                moveInfo.setText("Player " + game.player +
                " hit reverse, No moves to reverse, Player 1's turn");
            } else {
                final int i = pos/7;
                final int j = pos%7;
                if (game.theme == 1) {
                    buttons.get(pos/7).get(pos%7).unpress(ub1);
                } else if (game.theme == 2) {
                    buttons.get(pos/7).get(pos%7).unpress(ub2);
                } else {
                    buttons.get(pos/7).get(pos%7).unpress(ub3);
                }
                final int op;
                if (game.player == 1) {
                    op = 2;
                } else {
                    op = 1;
                }
                moveInfo.setText("Player " + op + " reversed move at " +
                                 (i+1) + "," + (j+1) + " Player " + game.player +
                                 "'s turn");
                turn.setText("Player " + game.player + "'s turn");
            }
        });

        // new game
        ng.setOnAction(e-> {
            final int size = game.size();
            for (int i = 0; i < size; i++) {
                int pos = game.reverse(buttons);
                if (game.theme == 1) {
                    buttons.get(pos/7).get(pos%7).unpress(ub1);
                } else if (game.theme == 2) {
                    buttons.get(pos/7).get(pos%7).unpress(ub2);
                } else {
                    buttons.get(pos/7).get(pos%7).unpress(ub3);
                }
            }
            turn.setText("Player 1's turn");
            moveInfo.setText("Player 1's turn");
        });

        playAgain.setOnAction(e-> {
            final int size = game.size();
            for (int i = 0; i < size; i++) {
                int pos = game.reverse(buttons);
                if (game.theme == 1) {
                    buttons.get(pos/7).get(pos%7).unpress(ub1);
                } else if (game.theme == 2) {
                    buttons.get(pos/7).get(pos%7).unpress(ub2);
                } else {
                    buttons.get(pos/7).get(pos%7).unpress(ub3);
                }
            }
            turn.setText("Player 1's turn");
            moveInfo.setText("Player 1's turn");
        });

        // theme 1
        t1.setOnAction(e-> {
            root.setBackground(bg2);
            info.setBackground(bg2);
            board.setBackground(bg2);
            finalScreen.setBackground(bg2);
            test.setBackground(bg2);
            infoScreen.setBackground(bg2);

            moveInfo.setBackground(ac2);
            game.changeTheme(2);

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 7; j++) {
                    buttons.get(i).get(j).changeTheme(bt3, bt4);
                }
            }
        });

        t2.setOnAction(e-> {
            root.setBackground(bg3);
            info.setBackground(bg3);
            board.setBackground(bg3);
            finalScreen.setBackground(bg3);
            test.setBackground(bg3);
            infoScreen.setBackground(bg3);

            moveInfo.setBackground(ac3);
            game.changeTheme(3);

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 7; j++) {
                    buttons.get(i).get(j).changeTheme(bt5, bt6);
                }
            }
        });

        oT.setOnAction(e-> {
            root.setBackground(bg1);
            info.setBackground(bg1);
            board.setBackground(bg1);
            finalScreen.setBackground(bg1);
            test.setBackground(bg1);

            moveInfo.setBackground(ac1);
            game.changeTheme(1);

            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 7; j++) {
                    buttons.get(i).get(j).changeTheme(bt1, bt2);
                }
            }
        });
        
        htp.setOnAction(e-> {
            primaryStage.setScene(infoScene);
        });

        goBack.setOnAction(e-> {
            primaryStage.setScene(gamePlay);
        });

        //############################## Display ###########################################
        primaryStage.setScene(scene);

        play.setOnAction(e-> primaryStage.setScene(gamePlay));
        playAgain.setOnAction(e->primaryStage.setScene(gamePlay));
        exit.setOnAction(e->Platform.exit());
        ex.setOnAction(e->Platform.exit());

		primaryStage.show();
	}
}

// put text for how to play.
// write some comment if time left.