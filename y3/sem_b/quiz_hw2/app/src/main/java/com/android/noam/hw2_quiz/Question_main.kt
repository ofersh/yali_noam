package com.android.noam.hw2_quiz

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentPagerAdapter
import android.support.v4.app.FragmentStatePagerAdapter
import android.support.v4.view.PagerAdapter
import android.support.v4.view.ViewPager

class Question_main : AppCompatActivity() {

    private lateinit var  q_pager: ViewPager
    var questions : ArrayList<Question> = ArrayList()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_question_main)

        q_pager = findViewById<ViewPager>(R.id.q_pager)

        set_questions()

        var q_pager_adapter = ScreenSlidePagerAdapter(getSupportFragmentManager(), questions)
        q_pager.adapter = q_pager_adapter
    }

    fun set_questions(){
        questions = ArrayList()

        var opts = arrayListOf<String>()
        opts.add("7")
        opts.add("3")
        opts.add("1")
        opts.add("4")

        questions.add(Question("3+4?", opts, 0))
        questions.add(Question("This is the second quesiotn", opts, 0))

    }


     class ScreenSlidePagerAdapter (fragmentManager: FragmentManager, private val questions:ArrayList<Question>)
         : FragmentPagerAdapter(fragmentManager) {

        override fun getItem(position: Int): Fragment {
            return Question_frag.newInstance(questions[position])
        }


        override  fun getCount(): Int {
            return questions.size
        }
    }


}

