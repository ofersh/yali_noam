package com.example.noam.kotelmania

import java.util.*

var ID : Int = 0

const val SENT = "נשלח"
const val RECEIVED = "התקבל"


class Note (var title: String, var content: String)
{

    private val date: Calendar = Calendar.getInstance()
    private val id: Int = ID++
    var status: String = SENT

    fun updateStatus(){
        val dayBeforeYesterday = Calendar.getInstance()
        dayBeforeYesterday.add(Calendar.DAY_OF_MONTH, -2)
        if(date.before(dayBeforeYesterday)){
            status = RECEIVED
        }
    }

    fun isEditable() : Boolean{
        return status == SENT
    }

    fun serializeCalendar() : Long
    {
        return date.timeInMillis
    }

    fun setDate(timeInMillis: Long){
        date.timeInMillis = timeInMillis
    }
}
