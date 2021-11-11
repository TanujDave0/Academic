import javafx.application.Application;

import javafx.scene.Scene;

import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.Socket;
import java.util.ArrayList;
import java.util.function.Consumer;

public class Client extends Thread{

    Socket socket;	
	ObjectOutputStream out;
	ObjectInputStream in;
    private Consumer<Serializable> callback;

    String ip;
    int port;

    public InfoPass curr;

    boolean rec;

	Client(Consumer<Serializable> call, String a, int b) {
        callback = call;
        ip = a;
        port = b;
        rec = false;
    }

    public void run() {
        try {
            socket = new Socket(ip, port);
            out = new ObjectOutputStream(socket.getOutputStream());
            in = new ObjectInputStream(socket.getInputStream());
            socket.setTcpNoDelay(true);
        }
        catch (Exception e) {}

        InfoPass temp;

        while (true) {
            try {
                temp = (InfoPass)in.readObject();
                curr = temp;
                callback.accept(temp);
                
            } catch (Exception e) {}
        }
    }

    public void send(String letter) {
		try {
            curr.letter = letter;
			out.writeObject(curr);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

    public int getSize() {
        return curr.size;
    }

    public String getMessage() {
        return curr.message;
    }

    public String getCategory() {
        if (curr.catNum == 0) {
            return "";
        }
        return curr.Categories.get(curr.catNum-1);
    }

    public ArrayList<String> getCategories() {
        return curr.Categories;
    }

    public boolean gotMsg() {
        return rec;
    }

    public void setRec(boolean a) {
        rec = a;
    }

    public String getWord() {
        return curr.word;
    }

    public int getGuesses() {
        return curr.guesses;
    }
}
