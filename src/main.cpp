#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 20  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);

/** ICOSAHEDRON MAPPINGS **/
static const char icosahedron_neighbors[20][3] = {
  { 15,  2, 5 },    // 1
  { 7, 3, 1 },      // 2
  { 2, 9, 4 },      // 3
  { 5, 3, 11 },     // 4
  { 1, 4, 13 },     // 5
  { 16,  7, 15 },   // 6
  { 6, 8, 2 },      // 7
  { 7, 17,  9 },    // 8
  { 8, 10,  3 },    // 9
  { 9, 18,  11 },   // 10
  { 4, 10,  12 },   // 11
  { 13,  11,  19 }, // 12 
  { 14,  5, 12 },   // 13
  { 20,  15,  13 }, // 14
  { 6, 1, 14 },     // 15
  { 20,  17,  6 },  // 16
  { 16,  18,  8 },  // 17
  { 10,  17,  19 }, // 18
  { 20,  12,  18 }, // 19
  { 16,  14,  19 }  // 20
};

static const char map_icosahedron_hardware[20] = {
  1,  // 1
  5,  // 2
  6,  // 3
  7,  // 4
  8,  // 5
  3,  // 6
  4,  // 7
  19, // 8
  20, // 9
  15, // 10
  14, // 11
  13, // 12
  9,  // 13
  10, // 14
  2,  // 15
  17, // 16
  18, // 17
  16, // 18
  12, // 19
  11  // 20
};

// State variables
uint16_t step = 0;

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  strip.clear();
  strip.setPixelColor(map_icosahedron_hardware[step % PIXEL_COUNT]-1, strip.Color(0, 0, 0, 10));

  strip.show();

  delay(1000);
  step++;
}
