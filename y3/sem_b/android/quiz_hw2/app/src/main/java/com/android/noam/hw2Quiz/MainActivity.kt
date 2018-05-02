package com.android.noam.hw2Quiz

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.View
import android.widget.EditText

const val NUM_QUESTION_STR = "num_of_questions"
const val DEFAULT_QUESTION_NUM = 5

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

    }

    fun startQuiz(view : View){
        val editText : EditText = findViewById(R.id.number_of_questions)
        val numOfQs : Int =  if (editText.text.toString() == ""){
            DEFAULT_QUESTION_NUM
        }else{
            if (editText.text.toString().toInt() < 2)
                DEFAULT_QUESTION_NUM
            editText.text.toString().toInt()
        }
        intent = Intent(this, QuestionMain::class.java)
        intent.putExtra(NUM_QUESTION_STR, numOfQs)
        startActivity(intent)
    }
}
