package com.yali_noam.chattygroup;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.ArrayList;

public class ChatPartnersActivity extends AppCompatActivity {

    ListView listView;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_partners);

        findViewById(R.id.headerTitle).setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if(event.getDownTime() > 3000){
                    FirebaseAuth.getInstance().signOut();
                    startActivity(new Intent(getApplicationContext(), SplashActivity.class));
                    finish();
                }
                return false;
            }
        });

        listView = findViewById(R.id.listView);
        FirebaseDatabase.getInstance().getReference("users").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                ArrayList<User> users = new ArrayList<>();
                for (DataSnapshot u: dataSnapshot.getChildren()) {
                    User user = u.getValue(User.class);
                    if(!user.uid.equals(FirebaseAuth.getInstance().getCurrentUser().getUid()))
                        users.add(user);
                }
                listView.setAdapter(new ArrayAdapter<User>(ChatPartnersActivity.this,
                        android.R.layout.simple_list_item_1,
                        android.R.id.text1,
                        users){
                    @NonNull
                    @Override
                    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
                        TextView t = (TextView)super.getView(position, convertView, parent);
                        t.setTextAppearance(R.style.TextViewDefault);
                        t.setText(getItem(position).email);
                        return t;
                    }
                });
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                User user = (User) parent.getAdapter().getItem(position);
                Intent intent = new Intent(ChatPartnersActivity.this, ChatActivity.class);
                intent.putExtra("partnerUid", user.uid);
                intent.putExtra("partnerEmail", user.email);
                startActivity(intent);
            }
        });
    }

    public static class User{
        public String uid;
        public String email;
    }

}
