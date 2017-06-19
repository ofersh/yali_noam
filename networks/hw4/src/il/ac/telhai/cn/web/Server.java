/**
 * Created by noamstolero on 04/06/2017.
 */
package il.ac.telhai.cn.web;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;


public class Server {

    public static void main(String[] args) {
        Server s = null;
        int newPort=0;
        if (args.length!=2)
            System.out.println("Usage Server <PORT NUMBER> <ROOT FOLDER>");
        try {
            newPort=Integer.parseInt(args[0]);
        }catch (NumberFormatException e){
            e.printStackTrace();
            System.exit(1);
        }
        try {
            s= new Server(newPort,args[1]);
        } catch (IOException e) {
            e.printStackTrace();
        }
        s.startServer();

    }


    /****** ACTUAL SERVER CLASS *******/
    private int port;
    private String rootFolder;
    private ServerSocket serverSocket;



    //initalize new server.
    Server(int port,String folder) throws IOException {
        this.port=port;
        rootFolder=folder;
        serverSocket= new ServerSocket(port);
    }



    public void startServer()
    {
        Socket s;
        while (true) {
            try {
                System.out.println("waiting for connection on port: "+serverSocket.getLocalPort()+ "ip: " + serverSocket.getInetAddress());

                s = serverSocket.accept();
                SocketHandler sh = new SocketHandler(s,rootFolder);
                sh.run();


            } catch (IOException e) {
                e.printStackTrace();
            }
        }


    }








}
