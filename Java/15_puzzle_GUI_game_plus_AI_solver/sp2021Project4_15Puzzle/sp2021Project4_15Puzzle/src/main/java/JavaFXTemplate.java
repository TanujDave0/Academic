import javafx.application.Application;

import javafx.scene.Scene;

import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.animation.PauseTransition;

import javafx.application.Application;

import javafx.scene.control.*;
import javafx.geometry.*;
import javafx.scene.text.*; 
import javafx.scene.paint.Color;
import javafx.scene.layout.*;
import java.util.Collections;

import java.util.ArrayList;
import java.util.Stack;
import javafx.util.Duration;

import javafx.event.EventHandler;
import javafx.event.ActionEvent;

import javafx.stage.Stage;
import javafx.application.Platform;
import javafx.scene.*;
import javafx.scene.image.Image;

import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.*;
import javafx.animation.*;

public class JavaFXTemplate extends Application {
    GameLogic game;
    GridPane board;
    ArrayList<GameButton> buttons;

    Background bg1;
    Background bg;
    Background gpb;
    Background ac;
    Background bt1;
    Background zb;

    ArrayList<ArrayList<Integer>> A1Ans;
    ArrayList<ArrayList<Integer>> A2Ans;

    int sol;
    int count;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
        bg = new Background(new BackgroundFill(Color.WHITESMOKE, CornerRadii.EMPTY, Insets.EMPTY));
        gpb = new Background(new BackgroundFill(Color.WHITESMOKE, CornerRadii.EMPTY, Insets.EMPTY));
        ac = new Background(new BackgroundFill(Color.NAVY, CornerRadii.EMPTY, Insets.EMPTY));
        bt1 = new Background(new BackgroundFill(Color.GRAY, new CornerRadii(10), Insets.EMPTY));
        zb = new Background(new BackgroundFill(Color.WHITESMOKE, new CornerRadii(10), Insets.EMPTY));
        bg1 = new Background(new BackgroundFill(Color.LIGHTBLUE, CornerRadii.EMPTY, Insets.EMPTY));

		primaryStage.setTitle("Welcome to 15 puzzle!");
        game = new GameLogic();
        board = new GridPane();

        count = 0;

        Image ig = new Image("bg.jpg");
        BackgroundImage newImage = new BackgroundImage(ig, BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT,BackgroundSize.DEFAULT);
        Background imageBg = new Background(newImage);

        //############################ GAME PLAY SCREEN #########################################
        Menu gpM = new Menu("Game Play");
        Menu hTP = new Menu("Guide");
        Menu qT = new Menu("Quit");

        MenuItem newP = new MenuItem("New puzzle");
        MenuItem a1 = new MenuItem("Solve with AI-H1");
        MenuItem a2 = new MenuItem("Solve with AI-H2");
        MenuItem exit = new MenuItem("Exit");
        MenuItem seeSol = new MenuItem("See the solution");
        MenuItem guide = new MenuItem("Guide");
        gpM.getItems().add(newP);
        gpM.getItems().add(a1);
        gpM.getItems().add(a2);
        hTP.getItems().add(guide);
        qT.getItems().add(exit);
        gpM.getItems().add(seeSol);

        // menu bar
        MenuBar bar = new MenuBar();
        bar.getMenus().add(gpM);
        bar.getMenus().add(hTP);
        bar.getMenus().add(qT);

        buttons = new ArrayList<>();

        for (int i = 0; i < 16; i++) {
            buttons.add(new GameButton(bt1, zb, game.at(i)));
        }

        board = new GridPane();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                board.add(buttons.get(4*i + j), j, i);
            }
        }

        board.setHgap(10);
        board.setVgap(10);

        board.setAlignment(Pos.TOP_CENTER);
        // board.setBackground(bg);

        TextField info = new TextField("Welcome the game! Please see the 'Guide' to learn rules and dynamics.");
        info.setDisable(true);

        VBox test= new VBox(40, bar, info, board);
        test.setBackground(bg);

        Scene gamePlay = new Scene(test,700, 700);

        //############################ Final Scene ########################################
        Text finalMsg = new Text("You Finised the Puzzle!");
        finalMsg.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 50));
        finalMsg.setFill(Color.NAVY);

        Button playAgain = new Button("Play Again");
        Button ex = new Button("Exit");
        VBox finalScreen = new VBox(finalMsg, playAgain, ex);
        finalScreen.setAlignment(Pos.CENTER);

        finalScreen.setMargin(finalMsg, new Insets(0,0,100,0));
        finalScreen.setMargin(playAgain, new Insets(0,0,50,0));

        finalScreen.setBackground(imageBg);
		Scene finalScene = new Scene(finalScreen, 700,700);

        //########################### WELCOME SCREEN ##################################
        primaryStage.setScene(welcomeScreen());
		primaryStage.show();

        PauseTransition pause = new PauseTransition(Duration.seconds(3));
        pause.setOnFinished(e-> {
            primaryStage.setScene(gamePlay);
        });
        pause.play();

        //################################## GUDIE ####################################
        TextArea playText = new TextArea();
        playText.setFont(Font.font("Times New Roman", FontPosture.REGULAR, 15));

        playText.setText("How to Play:" + "\n" +
                        "     1. This game allows the user to solve interesting 15 puzzles."
                         +"\n"+
                         "     2. The user has to move the pieces by clicking on them such that the final board" 
                         +"\n"+ "     has all the numbers in order from lowest number to the highest."
                         +"\n"+
                         "     3. You can obtain the solution for the puzzle by using AI Heuristic1 or AI Heuristic2"
                         +"\n" + "     options from the menu option 'Gameplay'."
                         +"\n"+
                         "     4. Once the solution is available, you can use the see solution option to see your puzzle solve. "
                         +"\n"+
                         "     5. The puzzle solution can be obtained by clicking on either of the heuristic options in the menu "
                         +"\n"+ "     on top of the game window."
                         +"\n"+
                         "     6. The AI algorithms will automatically solve the puzzle and also provide with the first 10 steps of the solution."
                         +"\n"+
                         "Menu Options:"
                         +"\n"+
                         "     1. New Puzzle : Provides the user with a new puzzle."
                         +"\n"+
                         "     2. Solve with AI - H1 : This option can be used to get a solution to the puzzle by using one" 
                         +"\n"+ "     of the AI heuristics."
                         +"\n"+
                         "     3. Solve with AI - H2 : This option can be used to get a solution to the puzzle by using another" 
                         +"\n"+ "     AI heuristics."
                         +"\n" +
                         "     4. See the solution: Provides with a solution to the puzzle."
                         +"\n"+
                         "     5. Quit: Exits the game");

        playText.setDisable(true);
        playText.setPrefHeight(400);

        Button ret = new Button("Return to the game");
        
        VBox box = new VBox(30, playText, ret);
        box.setAlignment(Pos.CENTER);
        box.setBackground(bg1);

        Scene guideScreen = new Scene(box, 700, 700);

        exit.setOnAction(e->{
            System.exit(0);
        });

        guide.setOnAction(e-> {
            primaryStage.setScene(guideScreen);
        });

        ret.setOnAction(e-> {
            primaryStage.setScene(gamePlay);
        });

        for (int i = 0; i < 4; i++) {
            final int pos = i;
            for (int j = 0; j < 4; j++) {
                final int pos2 = j;
                buttons.get(4*i + j).setOnAction(e-> {
                    if (!buttons.get(4*pos + pos2).isZero()) {
                        final int x = game.getx();
                        final int y = game.gety();
                        
                        if ((x-1 == pos && y == pos2) || 
                            (x == pos && y-1 == pos2) ||
                            (x+1 == pos && y == pos2) ||
                            (x == pos && y+1 == pos2)) {

                            animate(pos, pos2);

                            if (game.checkWin()) {
                                primaryStage.setScene(finalScene);
                            }
                        }
                    }
                });
            }
        }

        newP.setOnAction(e-> {
            game.generate();
            info.setText("New puzzle generated. Best of luck!");
            newPuzzle();
        });

        ex.setOnAction(e->System.exit(0));

        playAgain.setOnAction(e->{
            game.generate();
            newPuzzle();
            info.setText("New puzzle generated. Best of luck!");
            primaryStage.setScene(gamePlay);
        });

        a1.setOnAction(new EventHandler<ActionEvent>(){
            public void handle(ActionEvent e) {
                sol = 1;
                seeSol.setDisable(true);

                Thread tata = new Thread(()-> {
                    info.setText("Using A* heuristic one to solve the puzzle, Please wait!");

                    ExecutorService t = Executors.newFixedThreadPool(10);
                    Future<ArrayList<ArrayList<Integer>>> ft = t.submit(new MyCallable(1, game.getPuzzle()));
                    try {
                        ArrayList<ArrayList<Integer>> ans = ft.get();
                        info.setText("Puzzle solved! Please press 'See the solution'.");
                        seeSol.setDisable(false);
                        A1Ans = ans;

                        if (A1Ans == null) {
                            info.setText("Puzzle cannot be solved! Please select 'New Puzzle'.");
                        }
                    } catch(Exception f) {}

                    t.shutdown();
                });

                tata.start();
            }
        });

        a2.setOnAction(new EventHandler<ActionEvent>(){
            public void handle(ActionEvent e) {
                sol = 2;
                seeSol.setDisable(true);

                Thread runnit = new Thread(()-> {
                    info.setText("Using A* heuristic two to solve the puzzle, Please wait!");

                    ExecutorService t = Executors.newFixedThreadPool(10);
                    Future<ArrayList<ArrayList<Integer>>> ft = t.submit(new MyCallable(2, game.getPuzzle()));
                    try {
                        ArrayList<ArrayList<Integer>> ans = ft.get();
                        info.setText("Puzzle solved! Please press 'See the solution'.");
                        seeSol.setDisable(false);
                        A2Ans = ans;

                        if (A2Ans == null) {
                            info.setText("Puzzle cannot be solved! Please select 'New Puzzle'.");
                        }
                    } catch(Exception f) {}

                    t.shutdown();
                });

                info.setText("Using A* heuristic two to solve the puzzle, Please wait!");
                runnit.start();
            }
        });

        seeSol.setOnAction(e-> {
            if (sol == 1 && A1Ans != null) {
                seeSol.setDisable(true);
                a1.setDisable(true);
                a2.setDisable(true);
                newP.setDisable(true);

                int size = A1Ans.size();
                if (size > 10) size = 10;
                info.setText("Showing the first 10 steps to solve the puzzle using heuristic one");

                Timeline t = new Timeline(new KeyFrame(Duration.seconds(2), new EventHandler<ActionEvent>() {
                    @Override
                    public void handle(ActionEvent action) {
                        solutionAnimate();              
                    }
                }));

                t.setCycleCount(size);
                t.setOnFinished(a->{
                    for (int z = 0; z < 16; z++) {
                        buttons.get(z).setDisable(false);
                    }
                    if (game.checkWin()) {
                        primaryStage.setScene(finalScene);
                    }

                    info.setText("Please continue solving the puzzle");
                    seeSol.setDisable(false);
                    a1.setDisable(false);
                    a2.setDisable(false);    
                    newP.setDisable(false);                
                });
                t.play();

            } else if (sol == 2 && A2Ans != null) {
                newP.setDisable(true);
                seeSol.setDisable(true);
                a1.setDisable(true);
                a2.setDisable(true);

                int size = A2Ans.size();
                if (size > 10) size = 10;

                Timeline t = new Timeline(new KeyFrame(Duration.seconds(2), new EventHandler<ActionEvent>() {
                    @Override
                    public void handle(ActionEvent action) {
                        solutionAnimate();
                    }
                }));

                t.setCycleCount(size);
                t.setOnFinished(a->{
                    for (int z = 0; z < 16; z++) {
                        buttons.get(z).setDisable(false);
                    }
                    if (game.checkWin()) {
                        primaryStage.setScene(finalScene);
                    }
                    seeSol.setDisable(false);
                    a1.setDisable(false);
                    a2.setDisable(false);
                    newP.setDisable(false);

                    info.setText("Please continue solving the puzzle");
                });
                t.play();
            } else {
                if (sol == 1 || sol == 2) {
                    info.setText("Please wait while the solution is derived");
                } else {
                    info.setText("Please select one of AI options to solve the puzzle first.");
                }
            }
        });
	}

    boolean inc() {
        count++;
        if (count < 11) return false;
        count = 0;
        return true;
    }    

    int[] convert(ArrayList<Integer> arr) {
        int size = arr.size();
        int[] ans = new int[size];
        int i = 0;

        for(Integer e: arr) {
            ans[i++] = e;
        }

        return ans;
    }

    int findDiff(int[] arr1, int[] arr2) {
        int size = arr1.length;

        for (int i = 0; i < size; i++) {
            if (arr1[i] != arr2[i] && arr1[i] != 0) {
                return i;
            }
        }

        return -1;
    }

    void solutionAnimate() {
        int s;
        if (sol == 1) s = A1Ans.size();
        else s = A2Ans.size();

        if (s == 1) {
            if (sol == 1) A1Ans.remove(0);
            else A2Ans.remove(0);
            changeSol(-1);
          
            return;
        }
        int pos;
        if (sol == 1) {
            pos = findDiff(convert(A1Ans.get(0)), convert(A1Ans.get(1)));
            A1Ans.remove(0);
        } else {
            pos = findDiff(convert(A2Ans.get(0)), convert(A2Ans.get(1)));
            A2Ans.remove(0);
        }

        int pos2 = pos%4;
        pos = pos/4;

        for (int z = 0; z < 16; z++) {
            buttons.get(z).setDisable(true);
        }

        if (pos == -1 || pos2 == -1) return;
        int x = game.getx();
        int y = game.gety();
        buttons.get(4*pos + pos2).press(ac);

        game.swap(pos,pos2);

        buttons.get(4*x + y).unpress(bt1, game.at(x,y));
        buttons.get(4*pos + pos2).unpress(zb, game.at(pos, pos2));
        buttons.get(4*pos + pos2).setDisable(true);
        buttons.get(4*x + y).setDisable(true);
    }

    void animate(int pos, int pos2) {
        if (pos == -1 || pos2 == -1) return;
        int x = game.getx();
        int y = game.gety();

        game.swap(pos,pos2);

        for (int z = 0; z < 16; z++) {
            buttons.get(z).setDisable(true);
        }

        PauseTransition p = new PauseTransition(Duration.seconds(0.5));
        p.setOnFinished(f-> {
            buttons.get(4*x + y).unpress(bt1, game.at(x,y));
            buttons.get(4*pos + pos2).unpress(zb, game.at(pos, pos2));

            
            for (int z = 0; z < 16; z++) {
                buttons.get(z).setDisable(false);
            }
        });

        p.play();
    }

    void changeSol(int num) {
        this.sol = num;
    }

    class MyCallable implements Callable<ArrayList<ArrayList<Integer>>> {
        int[] puzzle;
        ArrayList<ArrayList<Integer>> ans;
        int h;

        public MyCallable(int h, int[] puzzle) {
            this.puzzle = puzzle;
            this.h = h;
            ans = new ArrayList<ArrayList<Integer>>();
        }

        @Override
        public ArrayList<ArrayList<Integer>> call() throws Exception {
            A_IDS_A_15solver ids = new A_IDS_A_15solver(puzzle, h);

            ans = new ArrayList<>();
            ArrayList<Node> solution = ids.solution();

            for (int i = 0; i < 11 && i < solution.size(); i++) {
                addToSoltion(solution.get(i).getKey());
            }

            return ans;
        }

        void addToSoltion(int[] arr) {
            ArrayList<Integer> temp = new ArrayList<>();
    
            for (int e: arr) {
                temp.add(e);
            }
    
            ans.add(temp);
        }
    }

    void newPuzzle() {
        for (int i = 0; i < 16; i++) {
            buttons.get(i).change(bt1, zb, game.at(i));
        }
        if (A1Ans != null) A1Ans.clear();
        if (A2Ans != null) A2Ans.clear();
    }

    Scene welcomeScreen() {
        Text wel = new Text("Welcome to 15 Puzzle!");
        Text name = new Text("by Tanuj and Heet");

        wel.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 50));
        wel.setFill(Color.NAVY);
        name.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 10));
        wel.setFill(Color.BLUE);

        Background bg1 = new Background(new BackgroundFill(Color.LIGHTBLUE, CornerRadii.EMPTY, Insets.EMPTY));

        Image ig = new Image("bg.jpg");
        BackgroundImage newImage = new BackgroundImage(ig, BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT, BackgroundSize.DEFAULT);
        Background imageBg = new Background(newImage);

        VBox root = new VBox(20, wel, name);
        root.setBackground(imageBg);
        root.setAlignment(Pos.CENTER);
        Scene scene = new Scene(root, 700, 700);

        return scene;
    }

}
