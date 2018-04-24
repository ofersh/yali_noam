package cs.yali.noam.hw2_quiz

import com.github.kittinunf.fuel.android.extension.responseJson
import com.github.kittinunf.fuel.core.response
import com.github.kittinunf.fuel.httpGet
import com.github.kittinunf.result.Result
import org.json.JSONArray
import org.json.JSONObject


data class Question(var question : String, var options : ArrayList<String> , var right_answer : Int)



class QuestionCreator(var amount: Int = 5, var category : Int = 10, var level: String = "easy", var qType : String = "multiple"){

    private val SITE_URL = "https://opentdb.com/api.php?"
    private val AMOUNT = "amount="
    private val CATEGORY = "category="
    private val LEVEL = "difficulty="
    private val TYPE = "type="
    private val DELIM = '&'

    fun getOnlineQuestions() : JSONArray{

        var url = SITE_URL + AMOUNT + amount + DELIM + CATEGORY + category + DELIM + LEVEL + level + DELIM + TYPE + qType
        lateinit var qArray : JSONArray


        url.httpGet().responseJson { request, response, result ->
            when(result){
                is Result.Failure -> {
                    val ex = result.getException()
                }
                is Result.Success -> {
                    val data = result.get() as JSONObject
                    qArray = data["results"] as JSONArray

                }
            }
        }

        return qArray
    }




    fun set_questions(questions: ArrayList<Question>){

        questions.add(create_question(
                "What is the meaning of GOAT?",
                "Getting Of A Train",
                "Gliding On A Tomb",
                "Greatest Of All Time",
                "Giving Out All That",
                2
        ))

        questions.add(create_question(
                "Where is the annual Ginger Festival taking place?",
                "Netherlands",
                "Germany",
                "United States",
                "Guatemala",
                0
        ))

        questions.add(create_question(
                "When is the annual Ginger Festival happening?",
                "Last weekend of August",
                "First weekend of September",
                "First weekend of January",
                "Second weekend of July",
                1
        ))

        questions.add(create_question(
                "Some toilets have holes in the front part of the toilet seat. Why?",
                "If a snake would come from the toilet, so he would have a place to go",
                "For the male's testicals to have space",
                "To watch the you're own feces",
                "To make it easier for woman to wipe",
                3
        ))
        questions.add(create_question(
                "A picture",
                "Lion",
                "Koala",
                "Kauka",
                "Panda",
                2
        ))

    }

    fun create_question(q: String, opt1: String, opt2: String, opt3: String, opt4: String, right_answer: Int): Question{
        var opts = arrayListOf<String>()
        opts.add(opt1)
        opts.add(opt2)
        opts.add(opt3)
        opts.add(opt4)
        return Question(q, opts, right_answer)
    }

}