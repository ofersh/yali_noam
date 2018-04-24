package cs.yali.noam.hw2_quiz

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.AppCompatTextView
import android.view.View
import android.widget.*
import com.github.kittinunf.fuel.httpGet
import com.github.kittinunf.result.Result
import org.json.JSONObject

private const val CORRECT = "That was easy"
private const val MIDDLE = "Just a bit short"
private const val LOW = "Really?????"
private const val WRONG = "Good job. Don't let anyone tell you what is right"
private const val SHOW_PICTURE = "show picture"


class MainActivity : AppCompatActivity() {

    private var NUMBER_OF_QUESTIONS = 0
    private var curr_question = 0
    private var user_answers : BooleanArray? = null
    private var questions : ArrayList<Question> = ArrayList()

    private var t_question: TextView? = null
    private var r_group: RadioGroup? = null
    private var r_buttons: ArrayList<RadioButton> = ArrayList()

    private var async_running: Boolean = false
    private var threadFunctionActivated: String = ""


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Initialize Class Variables

        create_questions()
        user_answers = BooleanArray(size = NUMBER_OF_QUESTIONS)

        // Initialize View variables
        val answers_button = findViewById<Button>(R.id.save_answer)

        answers_button.setOnClickListener{
            save_answer_pressed()
        }

        t_question = findViewById<TextView>(R.id.question)
        r_group = findViewById<RadioGroup>(R.id.options)
        r_buttons.add(0, findViewById<RadioButton>(R.id.opt1))
        r_buttons.add(1, findViewById<RadioButton>(R.id.opt2))
        r_buttons.add(2, findViewById<RadioButton>(R.id.opt3))
        r_buttons.add(3, findViewById<RadioButton>(R.id.opt4))
        present_question()

    }

    // Prompting to user functions
    fun save_answer_pressed(){
        if(curr_question >= user_answers!!.size) {
            curr_question = 0
            finish()
            startActivity(intent) //restart activity after last question
        }
        if(curr_question+1 == user_answers!!.size){
            check_answer()
            last_question()
            curr_question++
            findViewById<Button>(R.id.save_answer).text = "Try Again?"
        }
        else{
            check_answer()
            curr_question++
            present_question()
        }
    }

    fun check_answer(){
        val chosen_id = r_group!!.checkedRadioButtonId
        val correct_id = r_buttons[questions[curr_question].right_answer].id

        user_answers!![curr_question] = chosen_id == correct_id
    }

    fun present_question(){
        r_group?.clearCheck()
        var question = questions[curr_question]
        if(question.question == SHOW_PICTURE) {
            t_question!!.visibility = View.GONE
            findViewById<ImageView>(R.id.animal_pic).visibility = View.VISIBLE
        }
        else
            t_question?.text = question.question

        for(i in 0..3){
            r_buttons[i].text = question.options[i]
        }
    }

    fun last_question(){
        val t_prompt = findViewById<AppCompatTextView>(R.id.final_result_text_prompt)
        val n_prompt = findViewById<AppCompatTextView>(R.id.final_result_number_prompt)

        val correct_answers = user_answers?.count { it }

        when(correct_answers){
            5 -> t_prompt.text = CORRECT
            3,4 -> t_prompt.text = MIDDLE
            1,2 -> t_prompt.text = LOW
            0 -> t_prompt.text = WRONG
        }

        n_prompt.text = correct_answers.toString() + "/" + NUMBER_OF_QUESTIONS.toString()
    }


    // Initialization of Question functions
    fun create_questions(){


    }

    fun create_question(q: String, opt1: String, opt2: String, opt3: String, opt4: String, right_answer: Int): Question{
        var opts = arrayListOf<String>()
        opts.add(opt1)
        opts.add(opt2)
        opts.add(opt3)
        opts.add(opt4)
        return Question(q, opts, right_answer)
    }

    public fun callBackRunning(str: String){
        async_running = false
        threadFunctionActivated = str
    }

    public fun callBackTrue(){
        async_running = true

    }

}
