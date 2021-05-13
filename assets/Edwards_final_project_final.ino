// Jessica Edwards, PS70 Final Project Code, Spring 2021

#include <FastLED.h>
#include <WiFi.h>                                 // esp32 library
#include <FirebaseESP32.h>                        // firebase library

#define FIREBASE_HOST ""                          // the project name address from firebase id
#define FIREBASE_AUTH ""                          // the secret key generated from firebase
#define WIFI_SSID ""                              // input your home or public wifi name
#define WIFI_PASSWORD ""                          // password of wifi ssid

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN1 12
#define PIN2 27
#define PIN3 33
#define PIN4 25
#define PIN5 4

#define NUM_LEDS    10
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 1000
long previousMillis = 0;
long interval = 1000 / UPDATES_PER_SECOND;  

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

String led_status = "";                                          // led status received from firebase
String hex = "";

//Define FirebaseESP32 data object
FirebaseData firebaseData;

void setup() {
    Serial.begin(115200);
    delay( 3000 ); // power-up safety delay

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                          // try to connect with wifi

    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    
    Serial.println();
    Serial.print("Connected to ");
    Serial.println(WIFI_SSID);
    Serial.print("IP Address is : ");
    Serial.println(WiFi.localIP());                                // print local IP address
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                  // connect to firebase
    Firebase.reconnectWiFi(true);
    Firebase.set(firebaseData, "/LED_STATUS", "off");              
    Firebase.set(firebaseData, "/COLOR", "");


    // Initialize five LED strips
    
    FastLED.addLeds<LED_TYPE, PIN1, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    

    FastLED.addLeds<LED_TYPE, PIN2, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
   

    FastLED.addLeds<LED_TYPE, PIN3, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    

    FastLED.addLeds<LED_TYPE, PIN4, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    

    FastLED.addLeds<LED_TYPE, PIN5, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    // Begin in the "off" setting
    
    currentPalette = CRGBPalette16(CRGB::Black);
    fill_solid( currentPalette, 10, CRGB::Black);
}


void loop()
{
    // Gone with the delay! Used millis() instead
    unsigned long currentMillis = millis();

    Firebase.get(firebaseData, "/LED_STATUS");                     // get led status input from firebase
    led_status = firebaseData.stringData();                        // change to e.g. intData() or boolData()
    Serial.println(led_status);
  
    Firebase.get(firebaseData, "/COLOR");  
    hex = firebaseData.stringData();    
    Serial.println(hex);

    if (led_status == "off") {                                     // compare the input of led status received from firebase
      
      if (currentMillis - previousMillis > interval) {             // save the last time you blinked the LED 
      
        previousMillis = currentMillis;   
        
        Serial.println("off");
        currentPalette = CRGBPalette16(CRGB::Black);               // solid black
        fill_solid( currentPalette, 10, CRGB::Black);
        
        static uint8_t startIndex = 0;
        startIndex = startIndex + 1;                               // startIndex increments control the speed (larger int = faster speed)
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
        
      }
    }

    else if (led_status == "color") {       
      if (currentMillis - previousMillis > interval) {
        Serial.println("color");
    
        long number = (long) strtol( &hex[1], NULL, 16);            // turn HEX string to RGB numbers
        int r = number >> 16;
        int g = number >> 8 & 0xFF;
        int b = number & 0xFF;
  
        currentPalette = CRGBPalette16(CRGB( r, g, b));
        fill_solid( currentPalette, 10, CRGB( r, g, b));
        static uint8_t startIndex = 0;
        startIndex = startIndex + 1;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }

   else if (led_status == "romantic") {            
      if (currentMillis - previousMillis > interval) {
        Serial.println("romantic");
        
        RomanticPalette();            
        currentBlending = LINEARBLEND;                               // built-in light show styles
        
        static uint8_t startIndex = 0;
        startIndex = startIndex + 10;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }
    
    else if (led_status == "vibes") {            
      if (currentMillis - previousMillis > interval) {
        Serial.println("vibes");
        
        currentPalette = PartyColors_p;           
        currentBlending = NOBLEND;
  
        static uint8_t startIndex = 0;
        startIndex = startIndex + 50;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
        }
    }
    
    
    else if (led_status == "sunrise") {
      if (currentMillis - previousMillis > interval) {
        Serial.println("sunrise");            
        SunrisePalette();
        currentBlending = LINEARBLEND;
        static uint8_t startIndex = 0;
        startIndex = startIndex + 10;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }
    
    else if (led_status == "chill") {
      if (currentMillis - previousMillis > interval) {
        Serial.println("chill");            
        ChillPalette();
        currentBlending = LINEARBLEND;
        static uint8_t startIndex = 0;
        startIndex = startIndex + 10;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }
    
    else if (led_status == "waves") {            
      if (currentMillis - previousMillis > interval) {
        Serial.println("waves");
        currentPalette = OceanColors_p;           
        currentBlending = LINEARBLEND;
        static uint8_t startIndex = 0;
        startIndex = startIndex + 10;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }
    
    else if (led_status == "winter") {
      if (currentMillis - previousMillis > interval) {
        Serial.println("winter");            
        WinterPalette();            
        currentBlending = LINEARBLEND;
        static uint8_t startIndex = 0;
        startIndex = startIndex + 10;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }
  
    else if (led_status == "christmas") {
      if (currentMillis - previousMillis > interval) {
        Serial.println("christmas");            
        ChristmasPalette();
        currentBlending = LINEARBLEND;
        static uint8_t startIndex = 0;
        startIndex = startIndex + 10;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }
  
    else if (led_status == "birthday") {
      if (currentMillis - previousMillis > interval) {
        Serial.println("birthday");            
        BirthdayPalette();
        currentBlending = LINEARBLEND;
        static uint8_t startIndex = 0;
        startIndex = startIndex + 50;
  
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
      }
    }
  
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for (int i = 0; i < NUM_LEDS; ++i) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void RomanticPalette()
{
    CRGB color1 = CRGB(92, 10, 60);
    CRGB color2 = CRGB(121, 21, 81);
    CRGB color3 = CRGB(245, 111, 134);
    CRGB color4 = CRGB(210, 65, 117);
    CRGB color5 = CRGB(188, 52, 118);
    
    
    currentPalette = CRGBPalette16(
                                   color1, color2, color3, color4, color5,
                                   color1, color2, color3, color4, color5,
                                   color1, color2, color3, color4, color5,
                                   color1);
}
    
void WinterPalette()
{
    CRGB color1 = CRGB(17, 60, 207);
    CRGB color2 = CRGB(191, 245, 253);
    CRGB color3 = CRGB(255, 255, 255);
    
    
    currentPalette = CRGBPalette16(
                                   color1, color2, color3, 
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1);
}

void SunrisePalette()
{
    CRGB color1 = CRGB(183, 44, 60);
    CRGB color2 = CRGB(255, 154, 0);
    CRGB color3 = CRGB(255,77,0);
    CRGB color4 = CRGB(255,103,0);
    CRGB color5 = CRGB(255, 219, 0);
    
    
    currentPalette = CRGBPalette16(
                                   color1, color2, color3, color4, color5,
                                   color1, color2, color3, color4, color5,
                                   color1, color2, color3, color4, color5,
                                   color1);
}

void ChristmasPalette()
{
    CRGB color1 = CRGB(255, 0, 0);
    CRGB color2 = CRGB(0, 255, 0);
    CRGB color3 = CRGB(202, 184, 81);
    
    
    currentPalette = CRGBPalette16(
                                   color1, color2, color3, 
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1);
}

void ChillPalette()
{
    CRGB color1 = CRGB(57, 162, 174);
    CRGB color2 = CRGB(113, 196, 194);
    CRGB color3 = CRGB(227, 188, 181);
    
    
    currentPalette = CRGBPalette16(
                                   color1, color2, color3, 
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1, color2, color3,
                                   color1);
}

void BirthdayPalette()
{
    CRGB color1 = CRGB(21, 35, 194);
    CRGB color2 = CRGB(3, 120, 252);
    CRGB color3 = CRGB(90, 31, 189);
    CRGB color4 = CRGB(255, 165, 255);
    CRGB color5 = CRGB(173, 68, 249);
    
    
    currentPalette = CRGBPalette16(
                                   color1, color2, color3, color4, color5,
                                   color1, color2, color3, color4, color5,
                                   color1, color2, color3, color4, color5,
                                   color1);
}