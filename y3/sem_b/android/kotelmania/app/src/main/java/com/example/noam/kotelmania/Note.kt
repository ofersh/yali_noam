package com.example.noam.kotelmania

import java.util.*

var ID_COUNTER : Int = 0

const val SENT = " נשלח"
const val RECEIVED = " התקבל"


class Note (var title: String, var content: String, val ID: Int? = ID_COUNTER++, dateInMillis: Long? = null)
{
    private val date: Calendar = Calendar.getInstance()
    var status: String = SENT

    init {
        if (dateInMillis != null) {
            date.timeInMillis = dateInMillis
            updateStatus()
        }
    }

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
}
