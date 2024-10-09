package com.example.automates

import android.content.Intent
import android.media.MediaPlayer
import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class HomePage: AppCompatActivity() {

    private lateinit var btn_start: Button
    private var mediaPlayer: MediaPlayer ? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.homepage)

        btn_start = findViewById(R.id.btn_start)

        btn_start.setOnClickListener(){

            mediaPlayer?.release()
            mediaPlayer = MediaPlayer.create(this, R.raw.welcome)
            mediaPlayer?.start()
            mediaPlayer?.setOnCompletionListener {
                it.release()
                mediaPlayer = null
            }

            val intent = Intent(this, MainActivity::class.java)
            startActivity(intent)


        }

    }
}