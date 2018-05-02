package com.android.noam.hw2Quiz

import android.content.Context
import android.os.Bundle
import android.support.v4.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.RadioGroup
import android.widget.RadioButton
import android.widget.TextView


// TODO: Rename parameter arguments, choose names that match
// the fragment initialization parameters, e.g. ARG_ITEM_NUMBER
private const val QUESTION = "question"
private const val OPTIONS = "options"
private const val RIGHTANSWER = "right_answer"
private const val QUESTION_NUMBER ="question_number"

/**
 * A simple [Fragment] subclass.
 * Activities that contain this fragment must implement the
 * [QuestionFrag.OnFragmentInteractionListener] interface
 * to handle interaction events.
 * Use the [QuestionFrag.newInstance] factory method to
 * create an instance of this fragment.
 *
 */
class QuestionFrag : Fragment() {
    // TODO: Rename and change types of parameters
    private var rightAnswer: Int = -1
    private var questionNumber: Int = -1
    private var radioGroup: RadioGroup? = null
    private var listener: OnFragmentInteractionListener? = null

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_question_frag, container, false)

        val qText = view.findViewById<TextView>(R.id.question)
        radioGroup = view.findViewById(R.id.options)
        val opt1 = view.findViewById<RadioButton>(R.id.opt1)
        val opt2 = view.findViewById<RadioButton>(R.id.opt2)
        val opt3 = view.findViewById<RadioButton>(R.id.opt3)
        val opt4 = view.findViewById<RadioButton>(R.id.opt4)

//        val button = view.findViewById<Button>(R.id.saveAnswer)
//        button.setOnClickListener{
//            val chosenAnswer = countCheckedRadioButtons(radioGroup!!.checkedRadioButtonId)
//            listener?.onFragmentInteraction(questionNumber, chosenAnswer )
//
//        }

        radioGroup!!.setOnCheckedChangeListener { group, checkedId ->
            listener?.onFragmentInteraction(questionNumber, getCheckedRadioButtons(checkedId))
        }

        val args = arguments

        if (args != null) {
            qText.text = args.getString(QUESTION)
            val optionsList = args.getStringArrayList(OPTIONS)
            opt1.text = optionsList[0]
            opt2.text = optionsList[1]
            opt3.text = optionsList[2]
            opt4.text = optionsList[3]
            rightAnswer = args.getInt(RIGHTANSWER)
            questionNumber = args.getInt(QUESTION_NUMBER)
        }

        return view
    }

    private fun getCheckedRadioButtons(id: Int): Int{
        return when(id){
            R.id.opt1 -> 0
            R.id.opt2 -> 1
            R.id.opt3 -> 2
            R.id.opt4 -> 3
            else -> -1
        }
    }

    override fun onAttach(context: Context) {
        super.onAttach(context)
        if (context is OnFragmentInteractionListener) {
            listener = context
        } else {
            throw RuntimeException(context.toString() + " must implement OnFragmentInteractionListener")
        }
    }

    override fun onDetach() {
        super.onDetach()
        listener = null
    }

    /**
     * This interface must be implemented by activities that contain this
     * fragment to allow an interaction in this fragment to be communicated
     * to the activity and potentially other fragments contained in that
     * activity.
     *
     *
     * See the Android Training lesson [Communicating with Other Fragments]
     * (http://developer.android.com/training/basics/fragments/communicating.html)
     * for more information.
     */
    interface OnFragmentInteractionListener {
        // TODO: Update argument type and name
        fun onFragmentInteraction(q_ind: Int, user_answer: Int)
    }

    companion object {

        @JvmStatic
        fun newInstance(question: Question, question_number: Int): QuestionFrag {
            val args = Bundle()
            args.putString(QUESTION, question.question)
            args.putStringArrayList(OPTIONS, question.options)
            args.putInt(RIGHTANSWER, question.right_answer)
            args.putInt(QUESTION_NUMBER, question_number)

            val questionFrag = QuestionFrag()
            questionFrag.arguments = args

            return questionFrag
        }
    }
}
