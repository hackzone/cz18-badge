
/**
   === PIN LAYOUT ===
   IR:
 * * D3 - Transmitter
 * * D7 - Receiver

   433MHz RF:
 * * D8 - Transmitter
 * * D2 - Receiver

   LED Strip:
 * * D4 - Input

   Buzzers:
 * * D5 & D6 - Buzzer 1
 * * D9 & D10 - Buzzer 2

   Buttons:
   A2 - Mode switch
   A3 - Slot select
   A6 - Learn
   A7 - Play

*/

#include <Arduino.h>
#include <Bounce2.h>

#define DEBUG 1

#if DEBUG
#  define DEBUGSERIAL(...) Serial.print(__VA_ARGS__);
#  define DEBUGSERIALN(...) Serial.println(__VA_ARGS__);
#else
#  define DEBUGSERIAL(...)
#  define DEBUGSERIALN(...)
#endif

#define DEBUGSERIALN(x) DEBUGSERIAL(x); DEBUGSERIAL("\n");

const int SLOT_COUNT = 4;
const int MODULE_COUNT = 3;
const int RF_MODULE = 0,
          IR_MODULE = 1,
          TUNE_MODULE = 2;

const int BUTTON_COUNT = 4;
const int DEBOUNCE_INTERVAL_MS = 50;
const int MODE_BUTTON = 0,
          SLOT_BUTTON = 1,
          LEARN_BUTTON = 2,
          PLAY_BUTTON = 3;
const int BUTTON_PINS[BUTTON_COUNT] = { A2, A3, A4, A5 };
const int BUTTON_INPUT_MODE = INPUT_PULLUP;
const boolean BUTTON_OPEN_HIGH = true;
const int BUTTON_UNDEFINED = -1;
Bounce BUTTONS[BUTTON_COUNT];

int module = RF_MODULE;
int slot = 0;

void setup_buttons();
int read_pressed_button();
void increment_switchable(int *variable, int max_count);

void setup() {
  Serial.begin(115200);
  setup_buttons();
}

void loop() {
  int read_button = read_pressed_button();
  if (read_button != BUTTON_UNDEFINED) {
    DEBUGSERIAL("Read button: ");
    DEBUGSERIALN(read_button);

    switch (read_button) {
      case MODE_BUTTON:
        increment_switchable(&module, MODULE_COUNT);
        slot = 0;
        DEBUGSERIAL("Switched to module #");
        DEBUGSERIALN(module);
        break;
      case SLOT_BUTTON:
        if (module == RF_MODULE || module == IR_MODULE) {
          increment_switchable(&slot, SLOT_COUNT);
          DEBUGSERIAL("Switched to slot #");
          DEBUGSERIAL(slot);
          DEBUGSERIAL(" within module #");
          DEBUGSERIALN(module);
        }
        break;
      case LEARN_BUTTON:
        // TODO: Learn according to selected module
        break;
      case PLAY_BUTTON:
        // TODO: Play according to the selected module
        break;
      default:
        // Do nothing if unknown
        break;
    }
  }
}

void setup_buttons() {
  for (int i = 0; i < BUTTON_COUNT; ++i) {
    BUTTONS[i].interval(DEBOUNCE_INTERVAL_MS);
    BUTTONS[i].attach(BUTTON_PINS[i], BUTTON_INPUT_MODE);
  }
}

int read_pressed_button() {
  int output = BUTTON_UNDEFINED;
  for (int i = 0; i < BUTTON_COUNT; ++i) {
    // The button is pressed if the value of read is the false when it is open high or true when it is open low
    // and it has been updated.
    if (BUTTONS[i].update() && (BUTTON_OPEN_HIGH != BUTTONS[i].read())) {

      if (output != BUTTON_UNDEFINED) {
        // Already read a button, so we have two buttons pressed at the same time
        // for now, this is undefined behaviour.
        return BUTTON_UNDEFINED;
      }

      output = i;
    }
  }

  return output;
}

void increment_switchable(int *variable, int max_count) {
  (*variable) = ((*variable) + 1) % max_count;
}
