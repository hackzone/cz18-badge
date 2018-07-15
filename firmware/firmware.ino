#include "common.h"
#include "buttons.h"
#include "eeprom.h"

#include <FastLED.h>

const uint8_t LED_DATA_PIN = 4;
const uint8_t LED_COUNT = 7;

const uint8_t DEBOUNCE_INTERVAL_MS = 15;
const uint8_t BUTTON_INPUT_MODE = INPUT;

Buttons buttons(BUTTON_INPUT_MODE, DEBOUNCE_INTERVAL_MS);

CRGB leds[LED_COUNT];
uint8_t module = RF_MODULE;
uint8_t slot = 0;

void (*learn_routines[])(uint8_t slot) = {NULL, NULL, NULL};
void (*play_routines[])(uint8_t slot) = {NULL, NULL, NULL};

void set_leds() {
    for(int i = 0; i < MODULE_COUNT; i++) {
        leds[i] = module == i ? CRGB::DarkGoldenrod : CRGB::Black;
    }

    for(int i = 0; i < SLOT_COUNT; i++) {
        leds[i + MODULE_COUNT] = slot == i ? CRGB::Turquoise : CRGB::Black;
    }

    FastLED.show();
};

void setup() {
  Serial.begin(115200);
  buttons.setup();

  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, LED_COUNT);
  FastLED.setBrightness(5);

  set_leds();
}

void loop() {
  Buttons::button_type read_button = buttons.currently_pressed();
  if (read_button != Buttons::NONE) {
    DEBUG_PRINT("Read button: ");
    DEBUG_PRINTLN(read_button);

    switch (read_button) {
      case Buttons::LEARN:
      case Buttons::MODE:
        increment_switchable(&module, MODULE_COUNT);
        DEBUG_PRINT("Switched to module #");
        DEBUG_PRINTLN(module);
        set_leds();
        break;
      case Buttons::PLAY:
      case Buttons::SLOT:
          increment_switchable(&slot, SLOT_COUNT);
          DEBUG_PRINT("Switched to slot #");
          DEBUG_PRINT(slot);
          DEBUG_PRINT(" within module #");
          DEBUG_PRINTLN(module);
        set_leds();
        break;
//      case Buttons::LEARN:
//        if(learn_routines[module]) {
//            learn_routines[module](slot);
//        }
//        break;
//      case Buttons::PLAY:
//          if(play_routines[module]) {
//              play_routines[module](slot);
//          }
//        break;
      default:
        // Do nothing if unknown
        break;
    }
  }
}

void increment_switchable(uint8_t *variable, int max_count) {
  (*variable) = ((*variable) + 1) % max_count;
}


