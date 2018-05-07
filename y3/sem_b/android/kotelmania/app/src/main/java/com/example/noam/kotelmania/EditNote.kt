package com.example.noam.kotelmania

import android.content.Intent
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_edit_note.*
import kotlinx.android.synthetic.main.content_edit_note.*

class EditNote : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_edit_note)
        var bundle = intent.extras

        editTitle.setText(bundle.getString(TITLE))
        editContent.setText(bundle.getString(CONTENT))

        check.setOnClickListener {
            var result = Intent()
            result.putExtra(TITLE, editTitle.text.toString() )
            result.putExtra(CONTENT, editContent.text.toString())
            setResult(0, result)
            finish()
        }
    }

}
