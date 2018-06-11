package com.example.noam.kotelmania

import android.content.Context
import android.media.AudioManager
import android.media.SoundPool
import android.os.Build
import android.widget.Toast

class SoundHelper (val context: Context ){

    lateinit var soundPool: SoundPool
    var quagSoundID : Int = 0
    var ready: Boolean = false

    init {
        soundPool = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            SoundPool.Builder().setMaxStreams(1).build()
        }else
            SoundPool(1, AudioManager.STREAM_MUSIC, 0)

        quagSoundID = soundPool.load(context, R.raw.giggidi,1)
        soundPool.setOnLoadCompleteListener { soundPool, sampleId, status ->
            ready = true
        }
    }

    fun playSound(){
        if (ready){
            soundPool.play(quagSoundID, 1F, 1F,0,0, 1F)
        }

    }
}