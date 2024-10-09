package com.example.automates

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.example.automates.R
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase

class MainActivity : AppCompatActivity() {
    private lateinit var database: DatabaseReference
    private lateinit var buttonOn: Button
    private lateinit var buttonOff: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Initialize Firebase Database reference
        database = FirebaseDatabase.getInstance().reference

        // Initialize buttons using findViewById
        buttonOn = findViewById(R.id.button_on)
        buttonOff = findViewById(R.id.button_off)

        // Set up click listeners
        buttonOn.setOnClickListener {
            turnLedOn()
        }

        buttonOff.setOnClickListener {
            turnLedOff()
        }
    }

    private fun turnLedOn() {
        // Update the existing "LED/analog" path to turn on the LED
        database.child("LED").child("analog").setValue(1) // Sends 1 to the Firebase database
    }

    private fun turnLedOff() {
        // Update the existing "LED/analog" path to turn off the LED
        database.child("LED").child("analog").setValue(0) // Sends 0 to the Firebase database
    }
}
