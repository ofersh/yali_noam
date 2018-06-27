package com.yali_noam.chattygroup;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.animation.OvershootInterpolator;
import android.widget.ImageView;

import com.google.firebase.auth.FirebaseAuth;

public class SplashActivity extends AppCompatActivity {

    int animationTime = 4000;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splash);

        ImageView logo = findViewById(R.id.logo);
        logo.animate()
                .rotationYBy(360*3)
                .setDuration(animationTime)
                .setInterpolator(new OvershootInterpolator())
                .start();

        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                if(FirebaseAuth.getInstance().getCurrentUser() == null){
                    startActivity(new Intent(SplashActivity.this, LoginActivity.class));
                    finish();
                }
                else {
                    startActivity(new Intent(SplashActivity.this, ChatPartnersActivity.class));
                    finish();
                }
            }
        }, animationTime+1500);
    }
}
