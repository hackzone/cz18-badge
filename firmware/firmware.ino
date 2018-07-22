#include <IRremote.h>
#include <FastLED.h>
#include "common.h"
#include "buttons.h"
#include "eeprom.h"
#include  "ir_protocols.h"
#include "rfmodule.h"


const uint8_t LED_DATA_PIN = 4;
const uint8_t LED_COUNT = 7;

const uint8_t DEBOUNCE_INTERVAL_MS = 10;
const uint16_t LEARN_TIMEOUT_MS = 10000;

bool ir_learn(uint8_t slot, bool reinit);
void ir_play(uint8_t slot);

void learn(bool starting);
bool (*learn_routines[])(uint8_t slot, bool reinit) = {&ir_learn, NULL, NULL};
void (*play_routines[])(uint8_t slot) = {&ir_play, NULL, NULL};

Buttons buttons(DEBOUNCE_INTERVAL_MS);
RFModule radio;

IRrecv ir(IR_RECV_PIN);
IRsend ir_send;
IRSlot ir_play_slot;
decode_results ir_results;

CRGB leds[LED_COUNT];

uint8_t module = RF_MODULE;
uint8_t slot = 0;

bool currently_learning = false;

void set_leds(bool learning) {
    for (int i = 0; i < MODULE_COUNT; i++) {
        leds[i] = module == i ? (learning ? CRGB::Green : CRGB::DarkGoldenrod) : CRGB::Black;
    }

    for (int i = 0; i < SLOT_COUNT; i++) {
        leds[i + MODULE_COUNT] = slot == i ? CRGB::Turquoise : CRGB::Black;
    }

    FastLED.show();
};

void setup() {
    Serial.begin(115200);
    buttons.setup();

    FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(leds, LED_COUNT);
    FastLED.setBrightness(50);

    ir.enableIRIn();
    set_leds(false);
}

void loop() {
    Buttons::button_type read_button = buttons.currently_pressed();
    if (!currently_learning) {
      set_leds(false);
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
              if (play_routines[module]) {
                  play_routines[module](slot);
              }
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

void learn(bool starting)
{
    static uint32_t learning_start = 0;

    uint32_t current_millis = static_cast<uint32_t>(millis());
    if (learn_routines[module] != NULL) {
        bool finished = false;
        
        if (starting) {
           set_leds(true);
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

bool ir_learn(uint8_t slot, bool reinit) {
  
    if (reinit)
    {
      ir.resume();
    }
    if (ir.decode(&ir_results)) 
    {
        IRSlot irslot;
        irslot.used = true;
        irslot.value = ir_results.value;
        irslot.address = ir_results.address;
        irslot.protocol = ir_results.decode_type;
        irslot.length = ir_results.bits;
        
        bool known = false;
        for (int i = 0; (i < SUPPORTED_IR_PROTOCOLS_LEN) && !known; ++i) 
        {
            known = irslot.protocol == SUPPORTED_IR_PROTOCOLS[i];
        }
        
        if (known) 
        {
            DEBUG_PRINT("Saving into IR slot: ");
            DEBUG_PRINT(slot);
            DEBUG_PRINT(" value: ");
            DEBUG_PRINT(irslot.value);
            DEBUG_PRINT(" mode: ");
            DEBUG_PRINTLN(irslot.protocol);
            eeprom_write_ir_slot(slot, &irslot);
        }
        return true;
    }
    return false;
}

void ir_play(uint8_t slot) {
    eeprom_read_ir_slot(slot, &ir_play_slot);
    uint32_t val = ir_play_slot.value;
    uint32_t addr = ir_play_slot.address;
    uint32_t len = ir_play_slot.length;

    if (ir_play_slot.used) {
        DEBUG_PRINT("Sending IR: ");
        DEBUG_PRINT(ir_play_slot.protocol);
        DEBUG_PRINT(" ");
        DEBUG_PRINT(val);
        DEBUG_PRINT(" ");
        DEBUG_PRINT(len);
        DEBUG_PRINT(" ");
        DEBUG_PRINTLN(addr);
    
        switch (ir_play_slot.protocol) {
            case AIWA_RC_T501:
                ir_send.sendAiwaRCT501(val);
                break;
            case DENON:
                ir_send.sendDenon(val, len);
                break;
            case JVC:
                ir_send.sendJVC(val, len, false);
                break;
            case NEC:
                ir_send.sendNEC(val, len);
                break;
            case PANASONIC:
                ir_send.sendPanasonic(addr, val);
                break;
            case RC5:
                ir_send.sendRC5(val, len);
                break;
            case RC6:
                ir_send.sendRC6(val, len);
                break;
            case SAMSUNG:
                ir_send.sendSAMSUNG(val, len);
                break;
            case SONY:
                ir_send.sendSony(val, len);
                break;
            case WHYNTER:
                ir_send.sendWhynter(val, len);
                break;
        }
    }
}


void increment_switchable(uint8_t *variable, int max_count) {
    (*variable) = ((*variable) + 1) % max_count;
}


