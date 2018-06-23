package Noam.Yali.chat_hw;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
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
import java.util.Date;

public class MainActivity extends AppCompatActivity {

    DatabaseReference messagesRef;
    ListView listView;
    ArrayList<Message> messages;
    EditText messageBox;
    MessagesListAdapter adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if(FirebaseAuth.getInstance().getCurrentUser() == null){
            startActivity(new Intent(this, LoginActivity.class));
            finish();
        }

        FirebaseDatabase database = FirebaseDatabase.getInstance();
        messagesRef = database.getReference("messages");

        messages = new ArrayList<>();
        listView = findViewById(R.id.listView);
        adapter = new MessagesListAdapter(this, messages);
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

        private static class ViewHolder {
            TextView messageTV;
            TextView dateTV;
            TextView senderTV;
        }

        public MessagesListAdapter(Context context, ArrayList<Message> messages) {
            super(context, R.layout.messages_list_item, messages);
            this.messages = messages;
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

            viewHolder.messageTV.setText(message.message);
            viewHolder.dateTV.setText(dateFormatter.format(message.date));
            viewHolder.senderTV.setText(message.sender + " says:");

            return convertView;
        }
    }
}
