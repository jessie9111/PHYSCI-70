/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN        5 
#define NUMPIXELS 10 
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

Adafruit_NeoPixel strip(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

char LED_STATUS;

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();
      if (value.length() > 0) { 
        for (int i = 0; i < value.length(); i++){
          LED_STATUS = value[i];
        }
      }
    }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello World");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  
  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS low to reduce draw (max = 255)
}

void loop() {

  strip.clear(); // Set all pixel colors to 'off'
  
  int val = (int)LED_STATUS;  // cast the char* as an int 
  
  if (val == 48) {              // ASCII code for the number 0
    strip.setPixelColor(0, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 49) {             // ASCII code for the number 1
    strip.setPixelColor(1, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 50) {              // ASCII code for the number 2
    strip.setPixelColor(2, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 51) {             // ASCII code for the number 3
    strip.setPixelColor(3, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 52) {              // ASCII code for the number 4
    strip.setPixelColor(4, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 53) {             // ASCII code for the number 5
    strip.setPixelColor(5, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 54) {             // ASCII code for the number 6
    strip.setPixelColor(6, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 55) {             // ASCII code for the number 7
    strip.setPixelColor(7, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 56) {             // ASCII code for the number 8
    strip.setPixelColor(8, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  else if (val == 57) {              // ASCII code for the number 9
    strip.setPixelColor(9, strip.Color(0, 150, 0));
    strip.show();   // Send the updated pixel colors to the hardware.
  }
  delay(2000);
}
