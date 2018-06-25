#include "common.h"
#include "buttons.h"

const int SLOT_COUNT = 4;
const int MODULE_COUNT = 3;
const int RF_MODULE = 0,
          IR_MODULE = 1,
          TUNE_MODULE = 2;
          
const int DEBOUNCE_INTERVAL_MS = 50;
const int BUTTON_INPUT_MODE = INPUT_PULLUP;
const bool BUTTON_OPEN_HIGH = true;
Buttons buttons(BUTTON_INPUT_MODE, DEBOUNCE_INTERVAL_MS, BUTTON_OPEN_HIGH);

int module = RF_MODULE;
int slot = 0;

void increment_switchable(int *variable, int max_count);

void setup() {
  Serial.begin(115200);
  buttons.setup();
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
        break;
      case Buttons::button_type::SLOT:
        if (module == RF_MODULE || module == IR_MODULE) {
          increment_switchable(&slot, SLOT_COUNT);
          DEBUG_PRINT("Switched to slot #");
          DEBUG_PRINT(slot);
          DEBUG_PRINT(" within module #");
          DEBUG_PRINTLN(module);
        }
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

void increment_switchable(int *variable, int max_count) {
  (*variable) = ((*variable) + 1) % max_count;
}
