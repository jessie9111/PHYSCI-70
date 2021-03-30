#include <WiFi.h>                                 // esp32 library
#include <FirebaseESP32.h>                        // firebase library

#define FIREBASE_HOST ""     // the project name address from firebase id
#define FIREBASE_AUTH ""     // the secret key generated from firebase
#define WIFI_SSID ""         // input your home or public wifi name
#define WIFI_PASSWORD ""     // password of wifi ssid

String fireString = "";    // led status received from firebase
int outpin = 4;
int ledpin = 5;

//Define FirebaseESP32 data object
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(ledpin, OUTPUT);
  pinMode(outpin, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // try to connect with wifi

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                   // print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);     // connect to firebase
  Firebase.reconnectWiFi(true);
  Firebase.set(firebaseData, "/LED_STATUS", "OFF"); // set initial string of "OFF"
}

void loop() {

  Firebase.get(firebaseData, "/LED_STATUS");   // get led status input from firebase
  fireString = firebaseData.stringData();      // change to e.g. intData() or boolData()
  Serial.println(fireString);
  
  if (fireString == "ON") {                    // compare the input of led status received from firebase
    Serial.println("Led Turned ON");
    digitalWrite(ledpin, HIGH);                // make output led ON
    digitalWrite(outpin, HIGH);                // send HIGH output signal
  }

  else if (fireString == "OFF") {              // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(ledpin, LOW);                 // make output led OFF
    digitalWrite(outpin, LOW);                 // send LOW output signal
  }

  else {
    Serial.println("Please send ON/OFF");
  }

  delay(1000);                                 // not strictly necessary
}
