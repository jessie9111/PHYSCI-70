#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32
#elif defined(ESP8266)
  #define TFT_CS         4
  #define TFT_RST        16                                            
  #define TFT_DC         5
#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
#endif

// For 1.14", 1.3", 1.54", and 2.0" TFT with ST7789:
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
  
  Serial.begin(9600);
  pinMode(12, INPUT);
  Serial.print(F("Hello! ST77xx TFT Test"));
 
  tft.init(135, 240);           // Init ST7789 240x135
  
  Serial.println(F("Initialized"));
  uint16_t time = millis();
  time = millis() - time;
  Serial.println(time, DEC);
  delay(500);
  
  tft.fillScreen(ST77XX_BLACK);
  
}

void loop() {

  if (digitalRead(12)) tft.fillScreen(ST77XX_WHITE);
  else tft.fillScreen(ST77XX_BLACK);

}
