package il.ac.telhai.cn.web;


import javax.swing.text.html.HTML;
import java.io.*;
import java.net.Socket;
import java.util.Scanner;

/**
 * Created by noamstolero on 04/06/2017.
 */
public class SocketHandler implements Runnable {

    private static final String FILENOTFOUND="404 File Not Found";
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
            bufferedWriter.write(answer);
            bufferedWriter.flush();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private String handleRequest() throws IOException
    {
        String request, fileFoler, httpver;
        HtmlResponse resp;

        /** read First line **/
        request=sc.next();
        if (!request.equalsIgnoreCase(GET))
            return BADREQUEST;
        fileFoler=sc.next();
        httpver=sc.next();
        /***/
        System.out.println(request + " " + fileFoler + " " + httpver);

        resp = fileHandler(fileFoler);

        return resp.getResponse();
    }

    // read the content of the file
    private String readFile(File file) throws IOException
    {
        // initialize variables
        StringBuilder sb = new StringBuilder();
        FileReader fr = new FileReader(file);
        BufferedReader br = new BufferedReader(fr);
        String line;

        // read from the file
        while((line = br.readLine()) != null) {
            sb.append(line).append("\n");
        }

        return sb.toString();
    }


    // get the index file. return null if not exist
    private File getIndexFile(String folder){

        String[] indexFiles = {"index.html" , "INDEX.HTML" ,"INDEX.HTM","index.htm"};

        for (String ind : indexFiles) {
            // build the index file name
            StringBuilder sb = new StringBuilder();
            sb.append(folder).append("/").append(ind);
            File f = new File(sb.toString());

            // check if the file exists
            if(f.exists())
                return f;
        }

        return null;
    }

    // get the appropriate response to the request
    private HtmlResponse fileHandler(String fileFoler){
        // initialize variables
        File file = new File(fileFoler);
        HtmlResponse resp = new HtmlResponse();

        // check if path exists if not return file not found answer
        if(!file.exists()) {
            resp.setRequestStatusCode(FILENOTFOUND);
            return resp;
        }

        // check if path is a directory
        if(file.isDirectory()){
            File index = getIndexFile(fileFoler);
            if(index==null) {
                // if no index file then send back list of files
                String[] list = file.list();
                resp.setContent(String.join("\n",list));
                return resp;
            }

            file = index;
        }

        // a file has been found. send back content
        try {
            resp.setContent(readFile(file));
            resp.setRequestStatusCode(OK);
        } catch (IOException e) {
            resp.setRequestStatusCode(FILENOTFOUND);
        }

        return  resp;

    }


}
