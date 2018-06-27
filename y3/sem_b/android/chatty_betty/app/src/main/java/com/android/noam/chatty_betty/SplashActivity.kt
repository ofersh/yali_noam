package com.android.noam.chatty_betty

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.animation.OvershootInterpolator
import android.widget.ImageView
import android.content.Intent
import android.os.Handler
import com.google.firebase.auth.FirebaseAuth




class SplashActivity : AppCompatActivity() {

    var animationTime = 4000

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_splash)


        val logo : ImageView = findViewById(R.id.logo)
        logo.animate()
                .rotationYBy((360*3).toFloat())
                .setDuration(animationTime.toLong())
                .setInterpolator(OvershootInterpolator())
                .start()

        Handler().postDelayed({
            if (FirebaseAuth.getInstance().currentUser == null) {
                startActivity(Intent(this@SplashActivity, LoginActivity::class.java))
                finish()
            } else {
                startActivity(Intent(this@SplashActivity, ChatPartnersActivity::class.java))
                finish()
            }
        }, (animationTime + 1500).toLong())

    }
}
