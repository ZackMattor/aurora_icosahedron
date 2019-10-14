#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 20  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRBW + NEO_KHZ800);

/** ICOSAHEDRON MAPPINGS **/
static const uint8_t icosahedron_neighbors[20][3] = {
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

static const uint8_t map_icosahedron_hardware[] = {
  0,  // 1
  4,  // 2
  5,  // 3
  6,  // 4
  7,  // 5
  2,  // 6
  3,  // 7
  18, // 8
  19, // 9
  14, // 10
  13, // 11
  12, // 12
  8,  // 13
  9,  // 14
  1,  // 15
  16, // 16
  17, // 17
  15, // 18
  11, // 19
  10  // 20
};


enum Direction { left, right, back };

static const Direction steps[] = { right, right, right, right, right };

// State variables
uint16_t step = 0;
uint8_t current = 1;
uint8_t prev = 5;

uint8_t next_surface_id(uint8_t previous_id, uint8_t current_id, Direction dir) {
  return 4;
}

uint8_t surface_id_to_led_id(uint8_t surface_id) {
  return map_icosahedron_hardware[surface_id - 1];
}

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  strip.clear();

  uint8_t next = next_surface_id(prev, current, steps[step % 5]);

  strip.setPixelColor(surface_id_to_led_id(next), strip.Color(0, 50, 0, 0));

  strip.show();

  delay(1000);
  step++;
}
