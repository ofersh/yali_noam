package il.ac.telhai.cn.web;

import java.io.PrintWriter;
import java.io.StringWriter;

/**
 * Created by noamstolero on 18/06/2017.
 */
public class HtmlResponse {

    private String httpVersion;
    private String requestStatusCode;
    private String contentLength;
    private String contentType;
    private String content;
    private String connection;
    private String HEADER_END;

    //default constructor, setting default fields.
    public HtmlResponse ()
    {
        httpVersion="HTTP/1.1";
        contentType="Content-Type: text/html\n";
        contentLength="Content-Length: 0\n";
        connection="Connection: Closed\n";
        HEADER_END="\n\r";
    }

    //set the content of message.
    public void setContent(String content) {
        StringBuilder sb = new StringBuilder();
        sb.append("Content-Length: ");
        sb.append(content.length());
        sb.append("\n");
        contentLength=sb.toString();
        this.content = content;
    }

    //set the request status code.
    public void setRequestStatusCode(String requestStatusCode) {
        this.requestStatusCode = requestStatusCode;

    }


    public String getResponse()
    {
        StringWriter sw = new StringWriter();
        PrintWriter pw = new PrintWriter(new StringWriter());
        pw.print(httpVersion+requestStatusCode+);



        return sw.toString();
    }


}
