#include "common.h"
#include "buttons.h"
#include "eeprom.h"

#include <FastLED.h>

const uint8_t LED_DATA_PIN = 4;
const uint8_t LED_COUNT = 7;

const uint8_t DEBOUNCE_INTERVAL_MS = 15;
const uint8_t BUTTON_INPUT_MODE = INPUT_PULLUP;
const bool BUTTON_OPEN_HIGH = true;

Buttons buttons(BUTTON_INPUT_MODE, DEBOUNCE_INTERVAL_MS, BUTTON_OPEN_HIGH);

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
        leds[i + MODULE_COUNT] = module == i ? CRGB::Turquoise : CRGB::Black;
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
  if (read_button != Buttons::button_type::NONE) {
    DEBUG_PRINT("Read button: ");
    DEBUG_PRINTLN(read_button);

    switch (read_button) {
      case Buttons::button_type::MODE:
        increment_switchable(&module, MODULE_COUNT);
        slot = 0;
        DEBUG_PRINT("Switched to module #");
        DEBUG_PRINTLN(module);
        set_leds();
        break;
      case Buttons::button_type::SLOT:
        if (module == RF_MODULE || module == IR_MODULE) {
          increment_switchable(&slot, SLOT_COUNT);
          DEBUG_PRINT("Switched to slot #");
          DEBUG_PRINT(slot);
          DEBUG_PRINT(" within module #");
          DEBUG_PRINTLN(module);
        }
        set_leds();
        break;
      case Buttons::button_type::LEARN:
        // TODO: Learn according to selected module
        break;
      case Buttons::button_type::PLAY:
        // TODO: Play according to the selected module
        break;
      default:
        // Do nothing if unknown
        break;
    }
  }
}

void increment_switchable(uint8_t *variable, int max_count) {
  (*variable) = ((*variable) + 1) % max_count;
}


