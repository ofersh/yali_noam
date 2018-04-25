package com.android.noam.hw2Quiz

import android.os.Build
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentPagerAdapter
import android.support.v4.view.ViewPager
import android.support.v7.app.AppCompatActivity
import android.text.Html
import android.view.View
import android.widget.TextView
import org.json.JSONArray
import org.json.JSONObject

const val NUMBER_OF_QUESTIONS = 5

class QuestionMain : AppCompatActivity(), QuestionFrag.OnFragmentInteractionListener {

    private var userAnswers : BooleanArray = BooleanArray(size = NUMBER_OF_QUESTIONS)
    private lateinit var  qPager: ViewPager
    private var answersProgressText : TextView? = null
    private var questions : ArrayList<Question> = ArrayList()


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_question_main)

        qPager = findViewById(R.id.q_pager)
        answersProgressText = findViewById(R.id.answers_progress)
        answersProgressText?.text = correctAnswerString()

        QuestionCreator().getOnlineQuestions(this)

    }

    private fun calcCorrectAnswers(): Int{
        return userAnswers.count { it }
    }

    private fun correctAnswerString(): String {
        val correctAnswers = calcCorrectAnswers()
        return correctAnswers.toString() + '/' + NUMBER_OF_QUESTIONS.toString()
    }


     class ScreenSlidePagerAdapter (fragmentManager: FragmentManager, private val questions:ArrayList<Question>)
         : FragmentPagerAdapter(fragmentManager) {

        override fun getItem(position: Int): Fragment {
            return QuestionFrag.newInstance(questions[position], position)
        }


        override  fun getCount(): Int {
            return questions.size
        }
    }

    // Played arround
//    fun checkAnswer(view:View){
//        if (view.id == R.id.saveAnswer) {
//            val qFrag = qPager.currentItem as QuestionFrag
//
//        }
//    }

    override fun onFragmentInteraction(q_ind: Int, user_answer: Int) {
        userAnswers[q_ind] = user_answer == questions[q_ind].right_answer
        answersProgressText!!.text = correctAnswerString()
        qPager.currentItem = q_ind+1 % NUMBER_OF_QUESTIONS

    }

    fun setQuestions (qJArray: JSONArray ){
        for(i in 0..(qJArray.length() -1)){
            val qJson = qJArray[i] as JSONObject
            val question = fromHtml(qJson["question"])
            val correct = fromHtml(qJson["correct_answer"])
            val answers = qJson["incorrect_answers"]  as JSONArray
            val answersArr = ArrayList<String>()
            for(j in 0..(answers.length() -1)) {
                answersArr.add(fromHtml(answers[j]))
            }
            answersArr.add(correct)

                questions.add(Question(question, answersArr, 3))
        }
        val qPagerAdapter = ScreenSlidePagerAdapter(supportFragmentManager, questions)
        qPager.adapter = qPagerAdapter
    }

}

fun fromHtml(html: Any) : String{
    val htmlStr = html as String
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
        return Html.fromHtml(htmlStr, Html.FROM_HTML_MODE_LEGACY).toString()
    } else {
        @Suppress("DEPRECATION")
        return Html.fromHtml(htmlStr).toString()
    }
}
