package com.android.noam.hw2Quiz

import com.github.kittinunf.fuel.android.extension.responseJson
import com.github.kittinunf.fuel.httpGet
import com.github.kittinunf.result.Result
import org.json.JSONArray


data class Question(var question : String, var options : ArrayList<String> , var right_answer : Int)


class QuestionCreator(private var amount: Int = 5,private var category : Int = 10,
                      private var level: String = "easy",private var qType : String = "multiple"){

    private val siteUrl = "https://opentdb.com/api.php?"
    private val amountStr = "amount="
    private val categoryStr = "category="
    private val levelStr = "difficulty="
    private val typeStr = "type="
    private val delimStr = '&'

    fun getOnlineQuestions(questionMain: QuestionMain){

        val url = siteUrl + amountStr + amount + delimStr + categoryStr + category + delimStr +
                levelStr + level + delimStr + typeStr + qType


        url.httpGet().responseJson { _, _, result ->
            when(result){
                is Result.Failure -> {
                    result.getException()
                }
                is Result.Success -> {
                    val data = result.get().obj()
                    val qArray = data["results"] as JSONArray
                    questionMain.setQuestions(qArray)
                }
            }
        }
    }

    fun setQuestions (questions: ArrayList<Question>){

        questions.add(createQuestion(
                "What is the meaning of GOAT?",
                "Getting Of A Train",
                "Gliding On A Tomb",
                "Greatest Of All Time",
                "Giving Out All That",
                2
        ))

        questions.add(createQuestion(
                "Where is the annual Ginger Festival taking place?",
                "Netherlands",
                "Germany",
                "United States",
                "Guatemala",
                0
        ))

        questions.add(createQuestion(
                "When is the annual Ginger Festival happening?",
                "Last weekend of August",
                "First weekend of September",
                "First weekend of January",
                "Second weekend of July",
                1
        ))

        questions.add(createQuestion(
                "Some toilets have holes in the front part of the toilet seat. Why?",
                "If a snake would come from the toilet, so he would have a place to go",
                "For the male's testicals to have space",
                "To watch the you're own feces",
                "To make it easier for woman to wipe",
                3
        ))
        questions.add(createQuestion(
                "A picture",
                "Lion",
                "Koala",
                "Kauka",
                "Panda",
                2
        ))

    }

    private fun createQuestion (q: String, opt1: String, opt2: String, opt3: String, opt4: String, right_answer: Int): Question{
        val opts = arrayListOf<String>()
        opts.add(opt1)
        opts.add(opt2)
        opts.add(opt3)
        opts.add(opt4)
        return Question(q, opts, right_answer)
    }

}