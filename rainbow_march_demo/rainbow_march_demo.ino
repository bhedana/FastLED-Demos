
/* rainbow_march_demo for FastLED 2.1 or greater

By: Andrew Tuline
Date: Oct, 2014

Rainbow marching up the strand. Pretty basic, but oh so popular, and we get a few options as well.

FastLED is available at https://github.com/FastLED/FastLED

*/



#include "FastLED.h"                                          // FastLED library. Preferably the latest copy of FastLED 2.1.
 
// Fixed definitions cannot change on the fly.
#define LED_DT 12                                             // Serial data pin for WS2812B or WS2801
#define COLOR_ORDER GRB                                       // Are they RGB, GRB or what??
#define LED_TYPE WS2812B                                       // What kind of strip are you using?
#define NUM_LEDS 24                                           // Number of LED's

// Initialize changeable global variables.
uint8_t max_bright = 128;                                      // Overall brightness definition. It can be changed on the fly.

struct CRGB leds[NUM_LEDS];                                   // Initialize our LED array.


// Initialize global variables for sequences
uint8_t thisdelay = 40;                                        // A delay value for the sequence(s)
uint8_t thishue = 0;                                          // Starting hue value.
int8_t thisrot = 1;                                           // Hue rotation speed. Includes direction.
uint8_t deltahue = 1;                                         // Hue change between pixels.
bool thisdir = 0;                                             // I use a direction variable, so I can plug into inputs in a standar fashion.

void setup() {
  Serial.begin(57600);
  LEDS.addLeds<LED_TYPE, LED_DT, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(max_bright);
  set_max_power_in_volts_and_milliamps(5, 500);                // FastLED 2.1 Power management set at 5V, 500mA
} // setup()



void loop () {
  ChangeMe();
  rainbow_march();
  show_at_max_brightness_for_power();                         // Power managed display of LED's.
  delay_at_max_brightness_for_power(2.5*thisdelay);           // Power managed FastLED delay.
  Serial.println(LEDS.getFPS());                            // Display frames per second in the serial monitor. Disable the delay in order to see how fast/efficient your sequence is.
} // loop()



void rainbow_march() {                                         // The fill_rainbow call doesn't support brightness levels
  if (thisdir == 0) thishue += thisrot; else thishue-= thisrot;  // I could use signed math, but 'thisdir' works with other routines.
  fill_rainbow(leds, NUM_LEDS, thishue, deltahue);             // I don't change deltahue on the fly as it's too fast near the end of the strip.
} // rainbow_march()



void ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  uint8_t secondHand = (millis() / 1000) % 60;                // Change '60' to a different value to change length of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    if (secondHand ==  0)  {thisrot=1; deltahue=5;}
    if (secondHand ==  5)  {thisdir=-1; deltahue=10;}
    if (secondHand == 10)  {thisrot=5;}
    if (secondHand == 15)  {thisrot=5; thisdir=-1; deltahue=20;}
    if (secondHand == 20)  {deltahue=30;}
    if (secondHand == 25)  {deltahue=2; thisrot=5;}
    if (secondHand == 30)  {}
    if (secondHand == 35)  {}
    if (secondHand == 40)  {}
    if (secondHand == 45)  {}
    if (secondHand == 50)  {}
    if (secondHand == 55)  {}
  }
} // ChangeMe()