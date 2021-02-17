#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 20  // Number of NeoPixels
#define NUM_ENTITIES 6

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

uint8_t step_count = 19;
static const Direction steps[] = { right, right, right, right,
                                   left, /*13*/right, right, left, right, left, right,
                                   left, right/*11*/, left, left, right, left, left, left };

uint32_t colors[] = {
  strip.Color(0, 200, 0, 0),
  strip.Color(0, 0, 200, 0),
  strip.Color(200, 0, 0, 0),
  strip.Color(200, 0, 200, 0),
  strip.Color(200, 200, 0, 0),
  strip.Color(0, 200, 200, 0)
};

// State variables
struct Entity {
  uint32_t step;
  uint8_t current;
  uint8_t prev;
  uint32_t color;
};

Entity entities[NUM_ENTITIES];

void reset() {
  for(int i=0; i<NUM_ENTITIES; i++) {
    entities[i] = ( Entity ) {0, 1, 5, colors[i]};
  }
}

uint8_t next_surface_id(uint8_t previous_id, uint8_t current_id, Direction dir) {
  uint8_t answer = 0;
  uint8_t neighbor_index = current_id-1;
  int8_t neighbor_adder = dir == left ? 1:2;

  for(uint8_t i=0; i<3; i++) {
    if(icosahedron_neighbors[neighbor_index][i] == previous_id) {
      answer = icosahedron_neighbors[neighbor_index][(i+neighbor_adder) % 3];
    }
  }

  return answer;
}

uint8_t surface_id_to_led_id(uint8_t surface_id) {
  return map_icosahedron_hardware[surface_id - 1];
}

void setup() {
  randomSeed(analogRead(0));
  //Serial.begin(9600);
  //Serial.print("Welcome!");
  strip.begin();
  strip.show();
  reset();
}

void loop() {
  strip.clear();

  strip.fill(strip.Color(0, 0, 250, 10), 0, PIXEL_COUNT);

  // Full walk
  //uint8_t next = next_surface_id(prev, current, steps[step % step_count]);
  //
  uint8_t next;

  for(int i=0; i<NUM_ENTITIES; i++) {
    entities[i];
    next = next_surface_id(entities[i].prev, entities[i].current, random(0, 2));
    strip.setPixelColor(surface_id_to_led_id(entities[i].current), entities[i].color);
    entities[i].prev = entities[i].current;
    entities[i].current = next;
    entities[i].step++;
  }

  if(next == 0) {
    delay(10000);
  }

  strip.show();

  delay(100);

  // Full walk
  //if(step == step_count+1) reset();
}
