import javafx.application.Application;

import javafx.scene.Scene;

import javafx.scene.layout.VBox;
import javafx.stage.Stage;

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

public class GUIServer extends Application {

    private Server server;
    private Scene scene;
    int port;
    ListView<String> listItems;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		launch(args);
	}

	//feel free to remove the starter code from this method
	@Override
	public void start(Stage primaryStage) throws Exception {
		// TODO Auto-generated method stub
		primaryStage.setTitle("Welcome to Server");

        Text message = new Text("Welcome to the Server");
        message.setFont(Font.font("Comic Sans", FontWeight.BOLD, FontPosture.REGULAR, 50));

        TextField userInput = new TextField("5555");

        Button enter = new Button("Next");

        VBox root = new VBox(message, userInput, enter);

        userInput.setPromptText("Please enter the port number to listen from/to");
        root.setAlignment(Pos.CENTER);
        root.setStyle("-fx-background-color: lightblue");

        listItems = new ListView<String>();

        enter.setOnAction(e-> { if (userInput.getText() == "") {
                                    userInput.setText("Please enter a valid port number");
                                } else {
                                    port = Integer.parseInt(userInput.getText());
                                    primaryStage.setScene(scene = createGUI());
                                    primaryStage.setTitle("This is the Server");
                                    server = new Server(data -> {
                                        Platform.runLater(()->{
                                            listItems.getItems().add(data.toString());
                                        });
                                }, port);
                            }
        });		
		
				
		Scene fP = new Scene(root, 700,700);
		primaryStage.setScene(fP);
		primaryStage.show();
	}

    private Scene createGUI() {
        BorderPane pane = new BorderPane();
		pane.setPadding(new Insets(70));
		pane.setStyle("-fx-background-color: coral");
        
        Text num = new Text("listening from port: " + String.valueOf(port));
        num.setFont(Font.font("Comic Sans", FontWeight.BOLD, FontPosture.REGULAR, 25)); 

        pane.setTop(num);
		
		pane.setCenter(listItems);
	
		return new Scene(pane, 700, 700);
    }

}
