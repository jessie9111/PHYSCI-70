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

const int sampleWindow = 500; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() {
  Serial.begin(9600);
  Serial.print(F("Hello! ST77xx TFT Test"));
  tft.init(135, 240);           // Init ST7789 240x135
  Serial.println(F("Initialized"));
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(3);
}

void loop() {

  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(0);   //reading DC pin from pin A1
    if (sample < 1024) { // toss out spurious readings
      if (sample > signalMax) {
        signalMax = sample;  // save just the max levels
      } else if (sample < signalMin) {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude

  Serial.println(peakToPeak);

  if (peakToPeak <= 50) {
    tft.fillScreen(ST77XX_WHITE);
  } else if (peakToPeak > 15) {
    tft.fillScreen(ST77XX_BLACK);
    testfillcircles(10, ST77XX_BLUE);
    testdrawtext("Yay!", ST77XX_MAGENTA);
  }
  
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextSize(6);
  tft.setTextWrap(true);
  tft.print(text);
}
