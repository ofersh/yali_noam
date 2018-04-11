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

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_question_main)
    }

    fun setupViewPager(){
        var adapter:
        //adapter = PagerAdapter(supportFragmentManager.get)

    }


     class ScreenSlidePagerAdapter (fragmentManager: FragmentManager, private val questions:ArrayList<Object>)
         : FragmentPagerAdapter(fragmentManager) {

        override fun getItem(position: Int): Fragment {
            return question_frag()
        }


        override  fun getCount(): Int {
            return questions.size
        }
    }


}

