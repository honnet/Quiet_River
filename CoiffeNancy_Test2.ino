#include "FastLED.h"

const int NUM_LEDS_RINGS  = 16;     /* 2 rings but controled similarly */
const int RINGS_DATA      = 9;

const int NUM_LEDS_STRIPS = 20;     /* 2 strips of 10 LEDs */
const int STRIPS_CLOCK    = 2;
const int STRIPS_DATA     = 3;


//CRGB led_rings[NUM_LEDS_RINGS];
CRGB led_strips[NUM_LEDS_STRIPS];

void setup() {
    delay( 3000 ); // power-up safety delay

//  FastLED.addLeds<NEOPIXEL, RINGS_DATA>(led_rings, NUM_LEDS_RINGS);
    FastLED.addLeds<WS2801, STRIPS_DATA, STRIPS_CLOCK, BGR>(led_strips, NUM_LEDS_STRIPS);
}

// Colors available: 0 red; 32 orange; 64 yellow; 96 green;
// 128 aqua; 160 blue; 192 purple; 224 pink; 255 red
void loop() {
    const int aqua = 128;
    const int pink = 224;
    const int wait = 50;

    color_fade(aqua, pink, wait);
}

//start HSV color, end HSV color, delay
void color_fade(uint16_t startColor, uint16_t endColor, uint8_t wait) {
    FastLED.clear();

    //loop around a color range from startColor to endColor
    for(int color = startColor; color < endColor; color++)
        push(color, wait);

    //loop around a color range from the end back to the start
    for(int color = endColor; color > startColor; color--)
        push(color, wait);
}

// ensures each "dot" up to the number of LEDs are all changed
inline void push(int color, uint8_t wait) {
    // set hue=color, Saturation = 255, Brightness = 127
    for(int dot = 0; dot < NUM_LEDS_STRIPS; dot++)
        led_strips[dot].setHSV(color, 255, 127);
    FastLED.show();  // update the LEDs

//  for(int dot = 0; dot < NUM_LEDS_RINGS; dot++)
//      led_rings[dot].setHSV(color, 255, 127);
//  FastLED.show();  // update the LEDs

    FastLED.delay(wait);
}

