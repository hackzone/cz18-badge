//
// Created by Tom on 25/07/2018.
//

#include "leds.h"

CRGB leds[LED_COUNT];

void set_leds(bool learning, bool playing) {
    for (int i = 0; i < MODULE_COUNT; i++) {
        leds[i] = module == i ? (learning ? CRGB::DarkRed : playing ? CRGB::DarkGreen : CRGB::DarkGoldenrod) : CRGB::Black;
    }

    for (int i = 0; i < SLOT_COUNT; i++) {
        leds[i + MODULE_COUNT] = slot == i ? CRGB::Turquoise : CRGB::Black;
    }

    FastLED.show();
};