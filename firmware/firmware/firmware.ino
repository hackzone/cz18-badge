
/**
 * === PIN LAYOUT ===
 * IR:
 * * D3 - Transmitter
 * * D7 - Receiver
 * 
 * 433MHz RF:
 * * D8 - Transmitter
 * * D2 - Receiver
 * 
 * LED Strip:
 * * D4 - Input
 * 
 * Buzzers:
 * * D5 & D6 - Buzzer 1
 * * D9 & D10 - Buzzer 2
 * 
 * Buttons:
 * A2 - Mode switch
 * A3 - Slot select
 * A4 - Learn
 * A5 - Play
 * 
 */
 
#include <Arduino.h>
#include <Bounce2.h>

#define DEBUG
#ifdef DEBUG
#define DEBUGSERIAL(x) Serial.print(x);
#else
#define DEBUGSERIAL(x) { };
#endif

#define DEBUGSERIALN(x) DEBUGSERIAL(x); DEBUGSERIAL("\n");

const int SLOT_COUNT = 4;
const int MODULE_COUNT = 3;
const int RF_MODULE = 0,
          IR_MODULE = 1,
          TUNE_MODULE = 2;

const int BUTTON_COUNT = 4;
const int DEBOUNCE_INTERVAL_MS = 5;
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
    
    switch(read_button) {
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
    // Is the button pressed?
    if (BUTTONS[i].update()) {
      // The button is pressed if the value of read is the false when it is open high or true when it is open low
      if (BUTTON_OPEN_HIGH != BUTTONS[i].read()) {
        
        if (output != BUTTON_UNDEFINED) {
          // Already read a button, so we have two buttons pressed at the same time
          // for now, this is undefined behaviour.
          return BUTTON_UNDEFINED;
        }
        
        output = i;
      }
    }
  }
  
  return output;
}

void increment_switchable(int *variable, int max_count) {
  (*variable) = ((*variable) + 1) % max_count;
}

/*
// Define the array of leds
CRGB leds[LED_STRIP_SIZE];
Volume vol;
IRrecv ir_receiver(IR_RECV_PIN);
RCSwitch mySwitch;
decode_results ir_decode;
int32_t code_expect = 0xff696897;
boolean lights = true;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  LEDS.addLeds<WS2812B,LED_STRIP_PIN,RGB>(leds,LED_STRIP_SIZE);
  LEDS.setBrightness(84);
  ir_receiver.enableIRIn();
  mySwitch.enableReceive(RC_RECV_INT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int current_received = 0;
  static uint8_t hue = 0;

  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }

  for(int i = 0; i < LED_STRIP_SIZE; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }

  // Now go in the other direction.  
  for(int i = (LED_STRIP_SIZE)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  
  if (ir_receiver.decode(&ir_decode)) {
    Serial.print("Received: ");
    Serial.print(ir_decode.value, HEX);
    current_received = ir_decode.value;
    Serial.println();
    ir_receiver.resume();
  }
  
  if (lights) {
    
  } else {
    
  }
}

void fadeall() { for(int i = 0; i < LED_STRIP_SIZE; i++) { leds[i].nscale8(250); } }
*/
