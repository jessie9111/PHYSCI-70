#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
    #include avr/power.h
#endif

#define PIN1 12
#define PIN2 27
#define PIN3 33
#define PIN4 25
#define PIN5 34

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(10, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(10, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(10, PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(10, PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(10, PIN5, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {

    strip1.begin();
    strip1.show(); // Initialize all pixels to 'off'

    strip2.begin();
    strip2.show(); // Initialize all pixels to 'off'

    strip3.begin();
    strip3.show(); // Initialize all pixels to 'off'

    strip4.begin();
    strip4.show(); // Initialize all pixels to 'off'

    strip5.begin();
    strip5.show(); // Initialize all pixels to 'off'
}

void loop() {
    // Some example procedures showing how to display to the pixels:
    colorWipe_all(strip1.Color(255, 0, 0), 50); // Red
    colorWipe_all(strip1.Color(0, 255, 0), 50); // Green
    colorWipe_all(strip1.Color(0, 0, 255), 50); // Blue
}

// Fill the dots one after the other with a color
void colorWipe_all(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i < strip1.numPixels(); i++) {
        strip1.setPixelColor(i, c);
        strip1.show();

        strip2.setPixelColor(i, c);
        strip2.show();

        strip3.setPixelColor(i, c);
        strip3.show();

        strip4.setPixelColor(i, c);
        strip4.show();

        strip5.setPixelColor(i, c);
        strip5.show();
        delay(wait);
    }
}