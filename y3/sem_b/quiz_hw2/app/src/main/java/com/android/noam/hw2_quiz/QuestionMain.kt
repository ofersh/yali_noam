package com.android.noam.hw2_quiz

import android.net.Uri
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.os.Looper
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentPagerAdapter
import android.support.v4.view.ViewPager
import android.support.v7.widget.AppCompatEditText
import android.text.Editable
import android.widget.EditText
import android.widget.TextView
import kotlinx.android.synthetic.main.fragment_question_frag.*

    private const val NUMBER_OF_QUESTIONS = 5
class Question_main : AppCompatActivity(), Question_frag.OnFragmentInteractionListener {

    private var user_answers : BooleanArray = BooleanArray(size = NUMBER_OF_QUESTIONS)
    private lateinit var  q_pager: ViewPager
    private var answers_progress_text : TextView? = null
    var questions : ArrayList<Question> = ArrayList()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_question_main)

        q_pager = findViewById<ViewPager>(R.id.q_pager)
        answers_progress_text = findViewById<TextView>(R.id.answers_progress)
        answers_progress_text?.setText(correct_answer_string())

        set_questions()

        val qPagerAdapter = ScreenSlidePagerAdapter(supportFragmentManager, questions)
        q_pager.adapter = qPagerAdapter
    }

    fun calc_correct_answers(): Int{
        var c : Int = 0
        for (a in user_answers)
            if (a)
                c++
        return c
    }

    fun correct_answer_string(): String {
        var correct_answers = calc_correct_answers()
        return correct_answers.toString() + '/' + NUMBER_OF_QUESTIONS.toString()
    }

    fun set_questions(){
        questions = ArrayList()

        val opts = arrayListOf<String>()
        opts.add("7")
        opts.add("3")
        opts.add("1")
        opts.add("4")

        questions.add(Question("3+4?", opts, 0))
        questions.add(Question("This is the second question", opts, 0))

    }


     class ScreenSlidePagerAdapter (fragmentManager: FragmentManager, private val questions:ArrayList<Question>)
         : FragmentPagerAdapter(fragmentManager) {

        override fun getItem(position: Int): Fragment {
            return Question_frag.newInstance(questions[position], position)
        }


        override  fun getCount(): Int {
            return questions.size
        }
    }

    override fun onFragmentInteraction(q_ind: Int, user_answer: Int) {
        user_answers[q_ind] = user_answer == questions[q_ind].right_answer
        answers_progress_text?.setText(correct_answer_string())
    }

}

