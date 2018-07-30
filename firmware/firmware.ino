 #include <IRremote.h>
#include "common.h"
#include "buttons.h"
#include "leds.h"
#include "eeprom.h"
#include "rfmodule.h"
#include "ir.h"
#include "sound.h"
#include "cybers.h"


#define DEBOUNCE_INTERVAL_MS 10
#define LEARN_TIMEOUT_MS 10000

void play();
void learn(bool starting);
bool (*learn_routines[])(uint8_t slot, bool reinit) = {&ir_learn, &rf_learn, &sound_learn, NULL};
void (*play_routines[])(uint8_t slot) = {&ir_play, &rf_play, &sound_play, NULL};

Buttons buttons(DEBOUNCE_INTERVAL_MS);

uint8_t module = RF_MODULE;
uint8_t slot = 0;

bool currently_learning = false;
bool currently_sending = false;

void setup() {
    Serial.begin(115200);
    buttons.setup();

    FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(LED_BRIGHTNESS);

    ir_init();
    rf_init();
    set_leds(false, false);

    cybercyber(&cybest);
}

void loop() {
    Buttons::button_type read_button = buttons.currently_pressed();
    if (!currently_learning) {
      set_leds(false, false);
      switch (read_button) {
          case Buttons::MODE:
              increment_switchable(&module, MODULE_COUNT);
              DEBUG_PRINT("Switched to module #");
              DEBUG_PRINTLN(module);
              break;
          case Buttons::SLOT:
              increment_switchable(&slot, SLOT_COUNT);
              DEBUG_PRINT("Switched to slot #");
              DEBUG_PRINT(slot);
              DEBUG_PRINT(" within module #");
              DEBUG_PRINTLN(module);
              break;
          case Buttons::LEARN:
              learn(true);
              break;
          case Buttons::PLAY:
              play();
              break;
          default:
              // Do nothing if unknown
              break;
      }
    } else {
      if (read_button == Buttons::MODE)
      {
          currently_learning = false;
          return;
      }
      learn(false);
    }
}

void learn(bool starting) {
    static uint32_t learning_start = 0;

    uint32_t current_millis = static_cast<uint32_t>(millis());
    if (learn_routines[module] != NULL) {
        bool finished = false;

        if (starting) {
           set_leds(true, false);
           learning_start = static_cast<uint32_t>(millis());
           currently_learning = true;
           finished = learn_routines[module](slot, true);

        } else {
           if ((current_millis - learning_start) > LEARN_TIMEOUT_MS)
           {
              currently_learning = false;
              return;
           }

           finished = learn_routines[module](slot, false);
        }

        currently_learning = !finished;
    }
}

void play() {
    set_leds(false, true);
    if (play_routines[module]) {
        play_routines[module](slot);
    }
    set_leds(false, false);
}

void increment_switchable(uint8_t *variable, int max_count) {
    (*variable) = ((*variable) + 1) % max_count;
}


