import java.io.IOException;
import java.net.URL;
import java.util.*;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import javafx.application.Platform;
import javafx.event.*;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.text.*;
import javafx.scene.control.*;

import javafx.geometry.Pos;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;

public class GUIClient extends Application {
    Background bg2 = new Background(new BackgroundFill(Color.BLACK, CornerRadii.EMPTY, Insets.EMPTY));

    private Client client;
    private Scene scene;
    int port;
    String ip;
    ListView<String> listItems;

    VBox root;
    TextField msg;

    Text cat1, cat2, cat3;

    Button c1, c2, c3;
    TextField c1tries, c2tries, c3tries;

    HBox h1, h2, h3;
    VBox v1, v2, v3;
    HBox cont;

    HBox info;
    VBox v4, v5, v6;
    Text t1,t2,t3;
    TextField category, word, size;

    VBox userInput;
    Text lt;
    TextField letter;

    HBox last;
    TextField guessesLeft;
    Button send;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Welcome to Client");

        Text message = new Text("Welcome to the Client");
        message.setFont(Font.font("Bauhaus 93", FontWeight.BOLD, FontPosture.REGULAR, 50));
        message.setText("Welcome to the Guess Game");
        message.setFill(Color.RED);
        TextField enterIP = new TextField("127.0.0.1");
        TextField enterPort = new TextField("5555");
        
        HBox userInput = new HBox(enterIP, enterPort);
        userInput.setPadding(new Insets(0,0,0,170));
        Button enter = new Button("Next");
        enter.setFont(Font.font("Arial", 18));
        enter.setText("Next");

        enterIP.setPromptText("Please enter the ip to connect to");
        enterPort.setPromptText("Please enter the port number to connect");
        
        
        root = new VBox(message, userInput, enter);
        root.setAlignment(Pos.CENTER);
        root.setStyle("-fx-background-color: whitesmoke");

        listItems = new ListView<String>();

        enter.setOnAction(e-> { port = Integer.parseInt(enterPort.getText());
                                ip = enterIP.getText();

                                client = new Client(data -> {
                                    Platform.runLater(()->{
                                        // listItems.getItems().add(data.toString());
                                        primaryStage.setScene(scene = createGUI(client.getCategories(),
                                                                        client.getMessage(),
                                                                        client.getSize(),
                                                                        "",
                                                                        "",
                                                                        client.getGuesses(),
                                                                        client));
                                        send.setOnAction(f->{   
                                            client.send(letter.getText());
                                            client.curr = (InfoPass) data;
                                            letter.clear();
                                        
                                            scene = createGUI(client.getCategories(),
                                                            client.getMessage(),
                                                            client.getSize(),
                                                            client.getWord(),
                                                            client.getCategory(),
                                                            client.getGuesses(),
                                                            client);
                                        });
                                    });
                                }, ip, port);

                                client.start();

                                primaryStage.setTitle("This is the Client");
                                
        });

        send = new Button("Send");

				
		Scene fP = new Scene(root, 700,700);
		primaryStage.setScene(fP);
		primaryStage.show();
	}

    private Scene createGUI(ArrayList<String> categories, String message, int sizeofWord, String w,
                            String cat, int guess, Client client) {
        msg = new TextField(message);
        msg.setEditable(false);
        msg.setAlignment(Pos.CENTER);

        cat1 = new Text("Category 1");
        cat2 = new Text("Category 2");
        cat3 = new Text("Category 3");
        cat1.setFont(Font.font("Times New Roman", 18));
        cat1.setFill(Color.BLUE);
        cat2.setFont(Font.font("Times New Roman", 18));
        cat2.setFill(Color.BLUE);
        cat3.setFont(Font.font("Times New Roman", 18));
        cat3.setFill(Color.BLUE);

        c1 = new Button(categories.get(0));
        c1tries = new TextField("3");
        c1tries.setEditable(false);
        c2tries = new TextField("3");
        c2tries.setEditable(false);
        c3tries = new TextField("3");
        c3tries.setEditable(false);
        c2 = new Button(categories.get(1));
        c3 = new Button(categories.get(2));

        h1 = new HBox(10, c1, c1tries);
        h2 = new HBox(10, c2, c2tries);
        h3 = new HBox(10, c3, c3tries);

        v1 = new VBox(10, cat1, h1);
        v2 = new VBox(10, cat2, h2);
        v3 = new VBox(10, cat3, h3);

        cont = new HBox(10, v1, v2, v3);     
        cont.setAlignment(Pos.CENTER);

        category = new TextField(cat);
        word = new TextField(client.curr.word);
        size = new TextField(String.valueOf(sizeofWord));
        category.setEditable(false);
        word.setEditable(false);
        size.setEditable(false);

        t1 = new Text("Current Category");
        t2 = new Text("The Word so far");
        t3 = new Text("Size of the word");
        t1.setFill(Color.BLUE);
        t1.setFont(Font.font("Times New Roman", 18));
        t2.setFill(Color.BLUE);
        t2.setFont(Font.font("Times New Roman", 18));
        t3.setFill(Color.BLUE);
        t3.setFont(Font.font("Times New Roman", 18));

        v4 = new VBox(t1,category);
        v5 = new VBox(t2, word);
        v6 = new VBox(t3, size);

        info = new HBox(15, v4, v5, v6);
        info.setAlignment(Pos.CENTER);

        lt = new Text("Guess the letter");
        lt.setFill(Color.BLUE);
        lt.setFont(Font.font("Times New Roman", 18));
        letter = new TextField();
        letter.setPromptText("Enter the letter you want to guess");

        userInput = new VBox(10, lt, letter);
        userInput.setAlignment(Pos.CENTER);

        // send = new Button("Send");
        guessesLeft = new TextField("Guesses left: " + String.valueOf(guess));

        last = new HBox(10, send, guessesLeft);
        last.setAlignment(Pos.CENTER);
	
        root = new VBox(100, msg, cont, info, userInput, last);
        root.setStyle("-fx-background-color: whitesmoke");
        root.setAlignment(Pos.CENTER);

		return new Scene(root, 700, 700);
    }

}
