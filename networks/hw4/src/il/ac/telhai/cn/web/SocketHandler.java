package il.ac.telhai.cn.web;


import java.io.*;
import java.net.Socket;
import java.util.Scanner;

/**
 * Created by noamstolero on 04/06/2017.
 */
public class SocketHandler implements Runnable {

    private static final String BADREQUEST="400 Bad Request";
    private static final String GET="GET";
    private static final String OK="200 OK";


    private Socket s;

    //input streams.
    private Scanner sc;
    //outpustreams.
    private BufferedWriter bufferedWriter;





    public SocketHandler(Socket s) throws IOException {
        this.s=s;

        //init input Streams.
        InputStreamReader isr= new InputStreamReader(s.getInputStream());
        sc = new Scanner(isr);

        //init Output Streams.
        OutputStreamWriter osw= new OutputStreamWriter(s.getOutputStream());
        bufferedWriter =new BufferedWriter(osw);



    }


    @Override
    public void run()
    {
        String answer;
        try
        {
            answer=handleRequest();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private String handleRequest() throws IOException
    {
        String request, fileFoler, httpver, fileContents;

        /** read First line **/
        request=sc.next();
        if (!request.equalsIgnoreCase(GET))
            return BADREQUEST;
        fileFoler=sc.next();
        httpver=sc.next();
        /***/
        System.out.println(request + " " + fileFoler + " " + httpver);

        //fileContents=readFile(fileFoler);


        return "not complete";
    }

    private String readFile(String fileFoler)
    {
        return null;
    }


}
