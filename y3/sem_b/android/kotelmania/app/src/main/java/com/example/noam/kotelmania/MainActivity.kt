package com.example.noam.kotelmania

import android.app.Activity
import android.content.Context
import android.content.Intent
import android.graphics.Color
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import kotlinx.android.synthetic.main.activity_main.*


const val NEW_NOTE = -1
const val BLUEISH :String = "#03a9f4"
const val GREENISH :String = "#8bc34a"


class MainActivity : Activity() {


    private lateinit var listView: ListView
    private lateinit var dbHandler: NoteDBHelper
    private var notes: ArrayList<Note> = ArrayList()
    private var noteInProgress: Note? = null
    private var noteInProgressInd = 0
    private var adapter: BaseAdapter? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        dbHandler = NoteDBHelper(this, null, 1)
        notes = dbHandler.getAllNotes()
        Note.ID_COUNTER = dbHandler.getNoteMaxID() + 1

        listView = findViewById(R.id.listView)
        adapter = NotesAdapter(this, notes)
        listView.adapter = adapter
        listView.setOnItemClickListener { _, _, position, _ ->
            launchEditNote(position)
        }
        newNote.setOnClickListener {
            launchEditNote(NEW_NOTE)
        }
    }

    override fun onDestroy() {
        dbHandler.close()
        super.onDestroy()
    }

    private fun launchEditNote(index: Int) {
        val intent = Intent(this, EditNote::class.java)
        noteInProgress = if (index == NEW_NOTE) {
            noteInProgressInd = NEW_NOTE
            Note("", "")
        } else if (!notes[index].isEditable()){
            Toast.makeText(this, "לא ניתן לערוך, הפתק התקבל.", Toast.LENGTH_SHORT).show()
            return
        }else{
            noteInProgressInd = index
            notes.removeAt(index)
        }

        intent.putExtra(TITLE, noteInProgress!!.title)
        intent.putExtra(CONTENT, noteInProgress!!.content)
        startActivityForResult(intent, 0)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        if (data != null) {
            val title = data.getStringExtra(TITLE)
            val content = data.getStringExtra(CONTENT)
            if (title.isNotBlank() or content.isNotBlank()) {
                noteInProgress!!.title = title
                noteInProgress!!.content = content
                if (noteInProgressInd == NEW_NOTE){
                    notes.add(0, noteInProgress!!)
                    dbHandler.addNote(noteInProgress!!)
                }else{
                    notes.add(noteInProgressInd, noteInProgress!!)
                    dbHandler.updateNote(noteInProgress!!)
                }
            }else{
                if (noteInProgressInd!=-1)
                    dbHandler.delete(noteInProgress!!.ID.toString())
            }
            adapter!!.notifyDataSetChanged()
        }
    }
}

class NotesAdapter(private var activity: Activity, private var notes: ArrayList<Note>) : BaseAdapter() {
    override fun getView(position: Int, convertView: View?, parent: ViewGroup?): View {
        lateinit var listItem: RelativeLayout
        listItem = if (convertView == null) {
            val inflater = activity.getSystemService(Context.LAYOUT_INFLATER_SERVICE) as LayoutInflater
            inflater.inflate(R.layout.list_item, null) as RelativeLayout
        } else
            convertView as RelativeLayout

        val note: Note = notes[position]
        val title: TextView = listItem.findViewById(R.id.title)
        val content: TextView = listItem.findViewById(R.id.content)
        val status: TextView = listItem.findViewById(R.id.status)
        title.text = note.title
        content.text = note.content
        status.text = note.status

        // Update color base on status
        if (note.isEditable()){
            status.setBackgroundColor(Color.parseColor(BLUEISH))
        }else{
            status.setBackgroundColor(Color.parseColor(GREENISH))
        }

        return listItem
    }

    override fun getItem(position: Int): Any {
        return notes[position]
    }

    override fun getItemId(position: Int): Long {
        return position.toLong()
    }

    override fun getCount(): Int {
        return notes.size
    }

}