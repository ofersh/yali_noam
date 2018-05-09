package com.example.noam.kotelmania

import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteConstraintException
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteException
import android.database.sqlite.SQLiteOpenHelper
import android.support.annotation.IntegerRes
import android.util.Log
import junit.runner.Version

const val NOTE_ID= "note_id"
const val STATUS = "status"
const val TITLE = "title"
const val CONTENT = "content"
const val DATE = "date"


class NoteDBHelper(context: Context, name: String?,
                   factory: SQLiteDatabase.CursorFactory?, version: Int):
                    SQLiteOpenHelper(context, DATABASE_NAME, factory, version){

    override fun onCreate(db: SQLiteDatabase?) {
        db!!.execSQL(CREATE_NOTES_TABLE)
    }

    override fun onUpgrade(db: SQLiteDatabase?, oldVersion: Int, newVersion: Int) {
        db!!.execSQL("DROP TABLE IF EXISTS $TABLE_NAME")
        onCreate(db)
    }


    fun addNote(note: Note){
        val values = ContentValues()
        values.put(COLUMN_CONTENT, note.content)
        values.put(COLUMN_NOTE_ID, note.id.toString())
        values.put(COLUMN_STATUS, note.status)
        values.put(COLUMN_TITLE, note.title)

        val db = this.writableDatabase

        val retVal = db.insert(TABLE_NAME, null, values)
        if (retVal >= 1) {
            Log.v("@@@WWe", " Record inserted")
        } else {
            Log.v("@@@WWe", " Not inserted")
        }
        db.close()
    }

    fun getNote(note_id: String): Note?{
        val query =
                "SELECT * FROM $TABLE_NAME WHERE + $COLUMN_NOTE_ID +  = \"$note_id\""

        val db = this.writableDatabase
        val cursor = db.rawQuery(query, null)
        var note: Note? = null

        if(cursor.moveToFirst()){
            cursor.moveToFirst()

            val id = Integer.parseInt(cursor.getString(0))
            val title = cursor.getString(1)
            val content = cursor.getString(2)
            val status = cursor.getString(3)

            note = Note(title, content)
            cursor.close()
        }
        db.close()
        return note
    }

    fun deleteNote(note_id: String): Boolean{
        var result = false
        val query =
                "SELECT * FROM $TABLE_NAME WHERE + $COLUMN_NOTE_ID +  = \"$note_id\""
        val db = this.writableDatabase
        val cursor = db.rawQuery(query, null)

        if(cursor.moveToFirst()){
            val id = Integer.parseInt(cursor.getString(0))
            val retVal = db.delete(TABLE_NAME, "$COLUMN_NOTE_ID =?",
                    arrayOf(id.toString()))

            if (retVal >= 1) {
                Log.v("@@@WWe", " Record Removed")
                result = true
            } else {
                Log.v("@@@WWe", " Not deleted")
            }
            cursor.close()
        }
        db.close()
        return result
    }

    fun updateNote(note: Note){

        val db = this.writableDatabase

        val values = ContentValues()
        values.put(COLUMN_CONTENT, note.content)
        values.put(COLUMN_TITLE, note.title)

        val retVal = db.update(TABLE_NAME,
                values,
                "$COLUMN_NOTE_ID = ${note.id.toString()}",
                null)

        if (retVal >= 1) {
            Log.v("@@@WWe", " Record updated")
        } else {
            Log.v("@@@WWe", " Not updated")
        }
        db.close()
    }

    fun getAllNotes(): ArrayList<Note>{
        val notes = ArrayList<Note>()
        val db = this.writableDatabase
        var cursor: Cursor? = null
        try {
            cursor = db.rawQuery("SELECT * FROM $TABLE_NAME", null)
        } catch (e: SQLiteException) {
            db.execSQL(CREATE_NOTES_TABLE)
            return ArrayList()
        }

        var title: String
        var content: String
        if(cursor!!.moveToFirst() ){
            while(!cursor.isAfterLast){
                title = cursor.getString(cursor.getColumnIndex(COLUMN_TITLE))
                content = cursor.getString(cursor.getColumnIndex(COLUMN_CONTENT))
                notes.add(Note(title, content))
                cursor.moveToNext()
            }
        }
        return notes
    }

    companion object {
        private const val DATABASE_VERSION = 1
        private const val DATABASE_NAME = "notes.db"

        const val TABLE_NAME = "notes"
        const val COLUMN_NOTE_ID= "note_id"
        const val COLUMN_TITLE = "title"
        const val COLUMN_CONTENT = "content"
        const val COLUMN_STATUS = "status"
        const val COLUMN_DATE = "date"

        const val CREATE_NOTES_TABLE= ("CREATE TABLE " +
                TABLE_NAME + "(" +
                COLUMN_NOTE_ID + " INTEGER PRIMARY KEY, " +
                COLUMN_TITLE + " TEXT," +
                COLUMN_CONTENT + " TEXT," +
                COLUMN_STATUS + " TEXT" +
                ")")

    }

}