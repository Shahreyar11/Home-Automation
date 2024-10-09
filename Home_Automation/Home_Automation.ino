#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// WiFi Credentials
#define WIFI_SSID "Airtel"
#define WIFI_PASSWORD ""

// Firebase Credentials
#define API_KEY ""
#define DATABASE_URL ""

// Pin Definitions
#define RELAY_PIN 26  // Pin for the relay
#define LED1_PIN 2    // Pin for the LED (optional)

// Firebase Variables
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Connection Flags
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);  // Set relay pin as output
  pinMode(LED1_PIN, OUTPUT);    // Set LED pin as output (optional)

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected to WiFi, IP: ");
  Serial.println(WiFi.localIP());

  // Setup Firebase
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase SignUp OK");
    signupOK = true;
  } else {
    Serial.printf("SignUp Error: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK) {
    // Read the value of the "LED/analog" key from Firebase Realtime Database
    if (Firebase.RTDB.getInt(&fbdo, "/LED/analog")) {
      int ledState = fbdo.intData();  // Get the integer value

      // Control the relay based on the Firebase value (0 or 1)
      if (ledState == 1) {
        digitalWrite(RELAY_PIN, LOW);  // Turn the relay ON (AC bulb ON)
        digitalWrite(LED1_PIN, HIGH);   // Optional: Turn the LED ON for indication
        Serial.println("AC Bulb is ON");
      } else {
        digitalWrite(RELAY_PIN, HIGH);  // Turn the relay OFF (AC bulb OFF)
        digitalWrite(LED1_PIN, LOW);    // Optional: Turn the LED OFF
        Serial.println("AC Bulb is OFF");
      }
    } else {
      Serial.printf("Failed to read from Firebase: %s\n", fbdo.errorReason().c_str());
    }

    // Optional delay to prevent frequent reads
    delay(3000);
  }
}
