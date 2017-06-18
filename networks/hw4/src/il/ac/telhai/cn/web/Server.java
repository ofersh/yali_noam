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
//        if (args.length!=3)
//            System.out.println("Usage Server <PORT NUMBER> <ROOT FOLDER>");
//        try {
//            int newPort=Integer.parseInt(args[1]);
//        }catch (NumberFormatException e){
//            e.printStackTrace();
//            System.exit(1);
//        }
        try {
            s= new Server(4555,"");
            //Server s= new Server(Integer.parseInt(args[1]),args[2]);
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
                s = serverSocket.accept();
                SocketHandler sh = new SocketHandler(s);
                sh.run();


            } catch (IOException e) {
                e.printStackTrace();
            }
        }


    }








}
