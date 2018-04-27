package com.android.noam.hw2Quiz

import android.os.Build
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentPagerAdapter
import android.support.v4.view.ViewPager
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.LinearLayoutCompat
import android.text.Html
import android.text.Layout
import android.view.View
import android.widget.Button
import android.widget.LinearLayout
import android.widget.RelativeLayout
import android.widget.TextView
import com.android.noam.hw2Quiz.R.id.gone
import kotlinx.android.synthetic.main.activity_question_main.*
import org.json.JSONArray
import org.json.JSONObject



class QuestionMain : AppCompatActivity(), QuestionFrag.OnFragmentInteractionListener {

    private lateinit var userAnswers : IntArray
    private lateinit var  qPager: ViewPager
    private var questions : ArrayList<Question> = ArrayList()
    private var numberOfQuestions = 5

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_question_main)

        qPager = findViewById(R.id.q_pager)

        val finishButton = findViewById<Button>(R.id.finish)
        val nextQuestionButton = findViewById<Button>(R.id.nextQuestion)

        finishButton.setOnClickListener{
            finishTheQuiz(finishButton)
        }
        nextQuestionButton.setOnClickListener{
            moveToNextQuestion(nextQuestionButton)
        }

        QuestionCreator().getOnlineQuestions(this)
    }

    // Counting the amount of correct answers
    private fun calcCorrectAnswers(): Int{
        var n_correctAnswers = 0
        var arrLen = userAnswers.size - 1
        for (i in 0..arrLen){
            if(userAnswers[i] == questions[i].right_answer){
                n_correctAnswers++
            }
        }
        return n_correctAnswers
    }

    private fun correctAnswerString(): String {
        val correctAnswers = calcCorrectAnswers()
        return correctAnswers.toString() + '/' + numberOfQuestions.toString()
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


    override fun onFragmentInteraction(q_ind: Int, user_answer: Int) {
        userAnswers[q_ind] = user_answer
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

        numberOfQuestions = questions.size
        userAnswers = IntArray(size = numberOfQuestions)
        val qPagerAdapter = ScreenSlidePagerAdapter(supportFragmentManager, questions)
        qPager.adapter = qPagerAdapter
    }

    private fun moveToNextQuestion(view: View){

        var currentFrag = qPager.currentItem
        if(currentFrag == numberOfQuestions-1){
            return
        }

        qPager.currentItem = currentFrag+1 % numberOfQuestions

    }
    // Saving the entered answer by the user and moving to the next question
    fun finishTheQuiz(view: View){
        val outcomeLayout: LinearLayout = findViewById(R.id.outcome_layout)
        val outcomeText: TextView = findViewById(R.id.outcome_text)
        val outcomeNumber: TextView = findViewById(R.id.outcome_number)

        outcomeText.text = getString(R.string.outcome_text)
        outcomeNumber.text = correctAnswerString()

        qPager.visibility = View.GONE
        findViewById<RelativeLayout>(R.id.button_layout).visibility = View.GONE
        outcomeLayout.visibility = View.VISIBLE
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
