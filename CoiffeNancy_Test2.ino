#include "FastLED.h"
#include <avr/power.h>

#define NUM_STRIPS 2
#define NUM_LEDS_PER_STRIP 20
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
      delay( 3000 ); // power-up safety delay
      clock_prescale_set(clock_div_2);
      FastLED.addLeds<NEOPIXEL, 9>(leds, 6);
      FastLED.addLeds<WS2801, 3, 2, RGB>(leds,20);
}

void loop() {
      // Colour Fade between colour 1 to colour 2 and back again
      // all leds fade through colours specificed (0 red; 32 orange; 64 yellow; 96 green; 128 aqua; 160 blue; 192 purple; 224 pink; 255 red)
      colour_fade(160, 255, 50);
}

void colour_fade(uint16_t startColour, uint16_t endColour, uint8_t wait)  //start HSV colour, end HSV colour, delay
{  

       FastLED.clear();

       for(int myColour = startColour; myColour < endColour; myColour++) //loop around a colour range from startColour to endColour
       {
         for(int dot = 0; dot < NUM_LEDS; dot++) // this loop ensures each "dot" up to the number of LEDs are all changed
          { 
          leds[dot].setHSV(myColour, 255, 255);  // set hue=myColour, Saturation = 255, Brightness = 255
          }
          FastLED.show();  // update the LEDs
          delay(wait);
       }
       
       for(int myColour = endColour; myColour > startColour; myColour--) //loop around a colour range from the end back to the start
       {
         for(int dot = 0; dot < NUM_LEDS; dot++) // this loop ensures each "dot" up to the number of LEDs are all changed
          { 
          leds[dot].setHSV(myColour, 255, 255);  // set hue=myColour, Saturation = 255, Brightness = 255
          }
          FastLED.show();  // update the LEDs
          delay(wait);
       }

  return;
}
