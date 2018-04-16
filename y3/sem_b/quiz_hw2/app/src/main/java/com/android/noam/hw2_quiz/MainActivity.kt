package com.android.noam.hw2_quiz

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val t = findViewById<TextView>(R.id.text_id)
        val t_id = t.id
        val r_t_id = R.id.text_id
        t.setText("ID from t.id: " + t_id.toString() + "\nID from R.id.text_id: " + r_t_id.toString())

    }

    fun start_quiz(view : View){
        intent = Intent(this, QuestionMain::class.java)
        startActivity(intent)
    }
}
