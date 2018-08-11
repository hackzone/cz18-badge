//
// Created by Tom on 25/07/2018.
//

#include "leds.h"

CRGB leds[LED_COUNT];

void do_torch() {
    FastLED.setBrightness(255 / 4 * (slot + 1));
    for(int i = 0; i < LED_COUNT; i++) {
        leds[i] = CRGB::White;
    }
    FastLED.show();
}

void set_leds(bool learning, bool playing) {
    if(module == TORCH_MODULE) { return do_torch(); }

    FastLED.setBrightness(LED_BRIGHTNESS);

    int module_led = module == RF_MODULE ? 2 : module == IR_MODULE ? 0 : 1;

    for (int i = 0; i < 3; i++) {
        leds[i] = module_led == i ? (learning ? CRGB::DarkRed : playing ? CRGB::DarkGreen : CRGB::DarkGoldenrod) : CRGB::Black;
    }

    for (int i = 0; i < SLOT_COUNT; i++) {
        leds[i + 3] = slot == i ? CRGB::Turquoise : CRGB::Black;
    }

    FastLED.show();
}

void do_disco(int note){
  // Map notes to led pattern
  byte map_led[] = { 1, 3, 2, 6, 4, 8, 24, 16, 48, 32, 96, 64};
  for (int i=0; i<7;i++)
  {
    leds[i] = CRGB::Black;
  }
  if (note == 0)
  {
    FastLED.show();
    return;
  } 
  note --;
  for (int i=0; i<7;i++)
    if(bitRead(map_led[note % 12],i))
      leds[i] = CRGB::Red;
  FastLED.show();
}

