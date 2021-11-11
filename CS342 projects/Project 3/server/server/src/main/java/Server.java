import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.function.Consumer;

import javafx.application.Platform;
import javafx.scene.control.ListView;

public class Server{
	int count = 1;
    int portNum;
	ArrayList<ClientThread> clients = new ArrayList<ClientThread>();
	TheServer server;
	private Consumer<Serializable> callback;
	
	Server(Consumer<Serializable> call, int port){
		callback = call;
		server = new TheServer();
		server.start();
        portNum = port;
	}

    public class TheServer extends Thread{
		public void run() {

			try(ServerSocket mysocket = new ServerSocket(portNum);){
                System.out.println("Server is waiting for a client!");
                callback.accept("Server is waiting for a client!");

                
                while(true) {
                    ClientThread c = new ClientThread(mysocket.accept(), count);
                    callback.accept("client has connected to server: " + "client #" + count);
                    clients.add(c);
                    c.start();
                    
                    count++;
                    }
            }
            catch(Exception e) {
                callback.accept("Server socket did not launch");
            }
		}
	}

    class ClientThread extends Thread{
        Socket connection;
        int count;
        ObjectInputStream in;
        ObjectOutputStream out;

        String word;

        GameLogic game;
        
        ClientThread(Socket s, int count){
            this.connection = s;
            this.count = count;

            game = new GameLogic();
        }
        
        public void updateClient() {
            try {
                out.writeObject(game.curr);
            }
            catch(Exception e) {}
        }
        
        public void run(){
                
            try {
                in = new ObjectInputStream(connection.getInputStream());
                out = new ObjectOutputStream(connection.getOutputStream());
                connection.setTcpNoDelay(true);	
            }
            catch(Exception e) {
                System.out.println("Streams not open");
                callback.accept("Streams not open with client: #" + count);
            }

            game.pickCat(1);
            
            updateClient();
                
            while(true) {
                try {
                    InfoPass temp = (InfoPass)in.readObject();

                    game.curr = temp;
                    
                    // game.pickCat(temp.catNum);
                    if (game.guess(temp.letter)) {
                        callback.accept("Client #" + count + " guessed a letter");
                    } else {
                        callback.accept("Client #" + count + " used a guess");
                    }                  

                    updateClient();
                }
                catch(Exception e) {
                    callback.accept("OOOOPPs...Something wrong with the socket from client: " + count + "....closing down!");
                    updateClient();
                    clients.remove(this);
                    break;
                }
            }
        }//end of run
    }
}