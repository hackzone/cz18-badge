//
// Created by Tom on 25/07/2018.
//

#ifndef FIRMWARE_LEDS_H
#define FIRMWARE_LEDS_H

#include <FastLED.h>
#include "common.h"

#define LED_COUNT 7
#define LED_DATA_PIN 4

extern CRGB leds[LED_COUNT];
void set_leds(bool learning, bool playing);
void do_disco(int note);

#endif //FIRMWARE_LEDS_H
