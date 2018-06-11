package com.example.noam.kotelmania

import java.util.*


const val SENT = " נשלח"
const val RECEIVED = " התקבל"
const val WAITING = "ממתין "


class Note (var title: String, var content: String, val ID: Int? = ID_COUNTER++, dateInMillis: Long? = null)
{
    private val date: Calendar = Calendar.getInstance()
    var status: String = WAITING

    init {
        if (dateInMillis != null) {
            date.timeInMillis = dateInMillis
            updateStatus()
        }
    }

    private fun updateStatus(){
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

    companion object {
        @JvmStatic var ID_COUNTER : Int = 0
    }
}
