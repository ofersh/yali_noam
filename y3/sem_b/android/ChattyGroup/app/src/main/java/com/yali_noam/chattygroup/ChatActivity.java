package com.yali_noam.chattygroup;

import android.content.Context;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.text.Spannable;
import android.text.SpannableString;
import android.text.style.StrikethroughSpan;
import android.text.style.StyleSpan;
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

public class ChatActivity extends AppCompatActivity {

    DatabaseReference messagesRef;
    ListView listView;
    ArrayList<Message> messages;
    EditText messageBox;
    MessagesListAdapter adapter;

    ArrayList<String> markWords;
    ArrayList<String> filterWords;
    Boolean markCompliments = false;



    ArrayList<String> curses = new ArrayList<>(
            Arrays.asList(new String[]{
                    "ugly",
                    "bitch",
                    "זין",
                    "fucker",
                    "fuck",
                    "pussy",
                    "cunt",
                    "dick"
                    }
            ));
    ArrayList<String> compliments = new ArrayList<>(
            Arrays.asList(new String[]{
                            "pretty",
                            "dude",
                            "חמוד",
                            "love",
                            "lovely",
                            "cute",
                            "beautiful",
                            "smart",
                            "dick"
                    }
            ));

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat);

        boldComplimentsfilterCurses();
        setupHeader();
        setupBody();
        setupConversationReference();
    }

    private void setupHeader() {
        String email = getIntent().getStringExtra("partnerEmail");
        TextView header = findViewById(R.id.headerTitle);
        header.setText(email);
    }

    private void setupBody() {
        messages = new ArrayList<>();
        listView = findViewById(R.id.listView);
        adapter = new MessagesListAdapter(this, messages, this);
        listView.setAdapter(adapter);
        messageBox = findViewById(R.id.messageBox);
    }

    private void setupConversationReference() {
        String uid = getIntent().getStringExtra("partnerUid");
        String uid2 = FirebaseAuth.getInstance().getCurrentUser().getUid();
        String chatKey = uid + uid2;
        if(uid.compareTo(uid2) > 0)
            chatKey = uid2 + uid;
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        messagesRef = database.getReference(chatKey);

        messagesRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                messages.clear();
                for (DataSnapshot postSnapshot: dataSnapshot.getChildren()) {
                    Message m = postSnapshot.getValue(Message.class);
                    messages.add(m);
                }
                adapter.notifyDataSetChanged();
                listView.postDelayed(new Runnable() {
                    @Override
                    public void run() {
                        listView.setSelection(messages.size()-1);
                    }
                }, 300);
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
       // closeKeyboard(view);
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

    public static class MessagesListAdapter extends ArrayAdapter<Message>{

        private ArrayList<Message> messages;
        private ChatActivity messageEditor;

        private static class ViewHolder {
            TextView messageTV;
            TextView dateTV;
            TextView senderTV;
        }

        public MessagesListAdapter(Context context, ArrayList<Message> messages, ChatActivity messageEditor) {
            super(context, R.layout.messages_list_item, messages);
            this.messages = messages;
            this.messageEditor = messageEditor;
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
                viewHolder.messageTV = convertView.findViewById(R.id.message);
                viewHolder.dateTV = convertView.findViewById(R.id.date);
                viewHolder.senderTV = convertView.findViewById(R.id.sender);
                convertView.setTag(viewHolder);
            } else {
                viewHolder = (ViewHolder) convertView.getTag();
            }

            SpannableString editedMessage = messageEditor.editMessage(message.message);
            viewHolder.messageTV.setText(editedMessage);
            viewHolder.dateTV.setText(dateFormatter.format(message.date));
            viewHolder.senderTV.setText(message.sender + " says:");

            return convertView;
        }

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

    public void switchEditor(View view) {
        if(markCompliments)
            boldCursesfilterCompliments();
        else
            boldComplimentsfilterCurses();
        adapter.notifyDataSetChanged();
    }


}
