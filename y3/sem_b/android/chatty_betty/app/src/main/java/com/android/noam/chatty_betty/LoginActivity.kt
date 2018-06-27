package com.android.noam.chatty_betty

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.KeyEvent
import android.view.View
import android.widget.EditText
import android.widget.AutoCompleteTextView
import android.view.inputmethod.EditorInfo
import android.widget.TextView
import com.android.noam.chatty_betty.R.id.email_sign_in_button


class LoginActivity : AppCompatActivity() {

    private lateinit var mEmailView : AutoCompleteTextView
    private lateinit var mPasswordView: EditText
    private lateinit var mProgressView: View
    private lateinit var mLoginFormView: View

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_login)

                mEmailView = findViewById(R.id.email)

        mPasswordView = findViewById(R.id.password);
        mPasswordView.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, Int id, KeyEvent keyEvent) {
                if (id == EditorInfo.IME_ACTION_DONE || id == EditorInfo.IME_NULL) {
                    attemptLogin();
                    return true;
                }
                return false;
            }
        });

        var mEmailSignInButton = email_sign_in_button
        mEmailSignInButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {
                attemptLogin();
            }
        });

        mLoginFormView = findViewById(R.id.login_form);
        mProgressView = findViewById(R.id.login_progress);
    }
}
