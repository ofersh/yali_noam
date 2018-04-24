package cs.yali.noam.hw2_quiz;


import android.os.Bundle;
import android.support.v4.widget.SwipeRefreshLayout;
import android.support.v7.app.AppCompatActivity;
import android.text.Html;
import android.widget.TextView;

import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.JsonHttpResponseHandler;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import cz.msebera.android.httpclient.Header;


public class InternetQuestions {

    JSONArray questions;
    MainActivity act;
    String question;

    public String getQuestions(String url){
        AsyncHttpClient client = new AsyncHttpClient();
        client.get("https://opentdb.com/api.php?amount=3&type=multiple", new JsonHttpResponseHandler() {
            @Override
            public void onSuccess(int statusCode, Header[] headers, JSONObject response) {
                try {
                    JSONArray arr = response.getJSONArray("results");
                    JSONObject obj = (JSONObject)arr.get(0);
                    question = Html.fromHtml(obj.getString("question")).toString();
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        });
        return question;
    }


}
