package com.example.noam.kotelmania

import java.util.*

var ID : Int = 0

class Note (var title: String, var content: String)
{
    private val id: Int = ID++
    var status: String = "נשלח"
    val date: Calendar = Calendar.getInstance()
}
