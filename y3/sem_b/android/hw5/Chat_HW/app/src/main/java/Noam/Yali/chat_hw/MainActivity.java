package Noam.Yali.chat_hw;

import android.content.Context;
import android.content.Intent;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.text.Html;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.style.StrikethroughSpan;
import android.text.style.StyleSpan;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    DatabaseReference messagesRef;
    ListView listView;
    ArrayList<Message> messages;
    EditText messageBox;
    MessagesListAdapter adapter;

    ArrayList<String> curses;
    ArrayList<String> compliments;
    ArrayList<String> markWords;
    ArrayList<String> filterWords;
    Boolean markCompliments = false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        curses = allCurses();
        compliments = allCompliments();
        boldComplimentsfilterCurses();


        if(FirebaseAuth.getInstance().getCurrentUser() == null){
            startActivity(new Intent(this, LoginActivity.class));
            finish();
        }

        FirebaseDatabase database = FirebaseDatabase.getInstance();
        messagesRef = database.getReference("messages");

        messages = new ArrayList<>();
        listView = findViewById(R.id.listView);
        adapter = new MessagesListAdapter(this, messages, this);
        listView.setAdapter(adapter);

        messageBox = findViewById(R.id.messageBox);

        messagesRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                messages.clear();
                for (DataSnapshot postSnapshot: dataSnapshot.getChildren()) {
                    Message m = postSnapshot.getValue(Message.class);
                    messages.add(m);
                }
                adapter.notifyDataSetChanged();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });
    }

    public void sendMessage(View view) {
        String key = messagesRef.push().getKey();
        Message m = new Message();
        m.message = messageBox.getText().toString();
        m.date = new Date();
        m.sender = FirebaseAuth.getInstance().getCurrentUser().getEmail();
        messagesRef.child(key).setValue(m);
        messageBox.setText("");
        closeKeyboard(view);
    }

    public void switchEditor(View view) {
        if(markCompliments)
            boldCursesfilterCompliments();
        else
            boldComplimentsfilterCurses();
        adapter.notifyDataSetChanged();
    }

    private void closeKeyboard(View view){
        view.clearFocus();
        InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        imm.hideSoftInputFromWindow(view.getWindowToken(), 0);
    }

    public static class Message{
        public String message;
        public Date date;
        public String sender;
    }

    public static class MessagesListAdapter extends ArrayAdapter<Message> {

        private ArrayList<Message> messages;
        private MainActivity messagesEditor;

        private static class ViewHolder {
            TextView messageTV;
            TextView dateTV;
            TextView senderTV;
        }

        public MessagesListAdapter(Context context, ArrayList<Message> messages, MainActivity messagesEditor) {
            super(context, R.layout.messages_list_item, messages);
            this.messages = messages;
            this.messagesEditor = messagesEditor;
        }

        SimpleDateFormat dateFormatter = new SimpleDateFormat("dd-MM-yyyy HH:mm");
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            Message message = getItem(position);
            ViewHolder viewHolder;

            if (convertView == null) {
                viewHolder = new ViewHolder();
                LayoutInflater inflater = LayoutInflater.from(getContext());
                convertView = inflater.inflate(R.layout.messages_list_item, parent, false);
                viewHolder.messageTV = (TextView) convertView.findViewById(R.id.message);
                viewHolder.dateTV = (TextView) convertView.findViewById(R.id.date);
                viewHolder.senderTV = (TextView) convertView.findViewById(R.id.sender);
                convertView.setTag(viewHolder);
            } else {
                viewHolder = (ViewHolder) convertView.getTag();
            }

            SpannableString editedMessage = messagesEditor.editMessage(message.message);
            viewHolder.messageTV.setText(editedMessage, TextView.BufferType.SPANNABLE);
            viewHolder.dateTV.setText(dateFormatter.format(message.date));
            viewHolder.senderTV.setText(message.sender + " says:");

            return convertView;
        }
    }

    private ArrayList<String> allCompliments() {
        ArrayList<String> compliments = new ArrayList<>();
        compliments.add("beautiful");
        compliments.add("strong");
        compliments.add("smart");
        return compliments;
    }

    private ArrayList<String> allCurses() {
        ArrayList<String> curses = new ArrayList<>();
        curses.add("ugly");
        curses.add("weak");
        curses.add("stupid");
        return curses;
    }

    public SpannableString editMessage(String message){

        // Initialize variables that will be used to edit the text
        SpannableString newMessage = new SpannableString(message);

        // Mark the words according to the configuration
        for(String word: markWords){
            StyleSpan boldStyle = new StyleSpan(Typeface.BOLD);
            int wordStartIndex = message.indexOf(word);
            int wordEndIndex = wordStartIndex + word.length();
            if(wordStartIndex >= 0){
                newMessage.setSpan(boldStyle, wordStartIndex, wordEndIndex, Spannable.SPAN_INCLUSIVE_INCLUSIVE);
            }
        }

        // Filter the words according to the configuration
        for(String word: filterWords){
            StrikethroughSpan strikethroughSpan = new StrikethroughSpan();
            int wordStartIndex = message.indexOf(word);
            int wordEndIndex = wordStartIndex + word.length();
            if(wordStartIndex >= 0){
                newMessage.setSpan(strikethroughSpan, wordStartIndex, wordEndIndex, Spannable.SPAN_INCLUSIVE_INCLUSIVE);
            }
        }
        return newMessage;
    }

//    private SpannableString markWords(SpannableString message){
//        for(String word: markWords){
//            int wordStartIndex = message.
//        }
//
//        return newMessage;
//    }
//
//    private SpannableString filterWords(SpannableString message){
//
//        for(String word: filterWords){
//            String filtered = new String(new char[word.length()]).replace("\0", "*");
//            newMessage = newMessage.replace(word, filtered);
//        }
//
//        return newMessage;
//    }

    private void boldComplimentsfilterCurses(){
        markWords = compliments;
        filterWords = curses;
        markCompliments = true;
    }

    private void boldCursesfilterCompliments(){
        markWords = curses;
        filterWords = compliments;
        markCompliments = false;
    }

}
