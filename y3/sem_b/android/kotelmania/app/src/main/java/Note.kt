import java.util.*

var ID : Int = 0

class Note (val id: Int = ID++, var title: String, var content: String,
            val date: Calendar = Calendar.getInstance(), var status: String = "Sent"){
}