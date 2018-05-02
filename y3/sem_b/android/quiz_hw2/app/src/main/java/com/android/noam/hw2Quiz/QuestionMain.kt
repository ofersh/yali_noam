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
import android.widget.*
import org.json.JSONArray
import org.json.JSONObject
import java.util.*


class QuestionMain : AppCompatActivity(), QuestionFrag.OnFragmentInteractionListener, ViewPager.OnPageChangeListener {


    private lateinit var userAnswers : IntArray
    private var numOfQuestions : Int = 0
    private lateinit var  qPager: ViewPager
    private var questions : ArrayList<Question> = ArrayList()
    private lateinit var finishButton : Button
    private lateinit var nextQuestionButton : Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_question_main)

        qPager = findViewById(R.id.q_pager)
        qPager.addOnPageChangeListener(this)
        finishButton = findViewById(R.id.finish)
        nextQuestionButton = findViewById(R.id.nextQuestion)

        finishButton.setOnClickListener{
            finishTheQuiz(finishButton)
        }
        nextQuestionButton.setOnClickListener{
            moveToNextQuestion(nextQuestionButton)
        }
        numOfQuestions = intent.extras.getInt(NUM_QUESTION_STR)
        QuestionCreator(amount = numOfQuestions).getOnlineQuestions(this)
    }

    // Counting the amount of correct answers
    private fun calcCorrectAnswers(): Int{
        var correctAnswers = 0
        val arrLen = userAnswers.size - 1
        for (i in 0..arrLen){
            if(userAnswers[i] == questions[i].right_answer){
                correctAnswers++
            }
        }
        return correctAnswers
    }

    private fun correctAnswerString(): String {
        val correctAnswers = calcCorrectAnswers()
        return correctAnswers.toString() + '/' + numOfQuestions.toString()
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
            val random = Random()
            val rightIndex : Int = random.nextInt(numOfQuestions - 1)
            answersArr.add(rightIndex, correct)
            questions.add(Question(question, answersArr, rightIndex))
        }

        numOfQuestions = questions.size
        userAnswers = IntArray(size = numOfQuestions)
        val qPagerAdapter = ScreenSlidePagerAdapter(supportFragmentManager, questions)
        qPager.adapter = qPagerAdapter
    }

    private fun moveToNextQuestion(view: View){

        val currentFrag = qPager.currentItem
        if(currentFrag == numOfQuestions -1){
            return
        }
        if (currentFrag == numOfQuestions -1){
            val finishButton = findViewById<Button>(R.id.finish)
            val nextQuestionButton = findViewById<Button>(R.id.nextQuestion)
            nextQuestionButton.visibility = View.GONE
            finishButton.visibility = View.VISIBLE
        }
        qPager.currentItem = currentFrag+1 % numOfQuestions

    }
    // Saving the entered answer by the user and moving to the next question
    private fun finishTheQuiz(view: View){
        val outcomeLayout: LinearLayout = findViewById(R.id.outcome_layout)
        val outcomeText: TextView = findViewById(R.id.outcome_text)
        val outcomeNumber: TextView = findViewById(R.id.outcome_number)

        outcomeText.text = getString(R.string.outcome_text)
        outcomeNumber.text = correctAnswerString()

        qPager.visibility = View.GONE
        findViewById<RelativeLayout>(R.id.button_layout).visibility = View.GONE
        outcomeLayout.visibility = View.VISIBLE
    }
    override fun onPageScrollStateChanged(state: Int) {
    }

    override fun onPageScrolled(position: Int, positionOffset: Float, positionOffsetPixels: Int) {
    }

    override fun onPageSelected(position: Int) {
        if(position == numOfQuestions -1){
            nextQuestionButton.visibility = View.GONE
            finishButton.visibility = View.VISIBLE
            return
        }else
        {
            finishButton.visibility = View.GONE
            nextQuestionButton.visibility = View.VISIBLE
        }
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
