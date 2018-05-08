package com.example.noam.kotelmania

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_edit_note.*
import kotlinx.android.synthetic.main.content_edit_note.*

class EditNote : AppCompatActivity() {

    lateinit var oldTitle : String
    lateinit var oldContent : String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit_note)
        val bundle = intent.extras

        oldTitle = bundle.getString(TITLE)
        oldContent = bundle.getString(CONTENT)
        editTitle.setText(oldTitle)
        editContent.setText(oldContent)

        check.setOnClickListener {
            val result = Intent()
            result.putExtra(TITLE, editTitle.text.toString() )
            result.putExtra(CONTENT, editContent.text.toString())
            setResult(0, result)
            finish()
        }
    }

    // No Change made.
    override fun onBackPressed() {
        val result = Intent()
        result.putExtra(TITLE, oldTitle )
        result.putExtra(CONTENT, oldContent)
        setResult(0, result)
        super.onBackPressed()
    }
}
