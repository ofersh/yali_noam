package com.android.noam.hw2_quiz

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
    private var right_answer: Int = -1
    private var question_number: Int = -1
    private var r_group: RadioGroup? = null
    private var listener: OnFragmentInteractionListener? = null

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?,
                              savedInstanceState: Bundle?): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_question_frag, container, false)

        val button = view.findViewById<Button>(R.id.save_answer)
        val q_text = view.findViewById<TextView>(R.id.question)
        r_group = view.findViewById<RadioGroup>(R.id.options)
        val opt1 = view.findViewById<RadioButton>(R.id.opt1)
        val opt2 = view.findViewById<RadioButton>(R.id.opt2)
        val opt3 = view.findViewById<RadioButton>(R.id.opt3)
        val opt4 = view.findViewById<RadioButton>(R.id.opt4)

        button.setOnClickListener{
            val chosen_answer = checked_radio_button_number(r_group!!.checkedRadioButtonId)
            listener?.onFragmentInteraction(question_number, chosen_answer )

        }

        val args = arguments

        if (args != null) {
            q_text.text = args.getString(QUESTION)
            val options_list = args.getStringArrayList(OPTIONS)
            opt1.text = options_list[0]
            opt2.text = options_list[1]
            opt3.text = options_list[2]
            opt4.text = options_list[3]
            right_answer = args.getInt(RIGHTANSWER)
            question_number = args.getInt(QUESTION_NUMBER)
        }

        return view
    }

    fun checked_radio_button_number(id: Int): Int{
        when(id){
            R.id.opt1 -> return 0
            R.id.opt2 -> return 1
            R.id.opt3 -> return 2
            R.id.opt4 -> return 3
            else -> return -1
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

            val question_frag = QuestionFrag()
            question_frag.arguments = args

            return question_frag
        }
    }
}
