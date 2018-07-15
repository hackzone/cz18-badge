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
const uint8_t BUTTON_INPUT_MODE = INPUT;

Buttons buttons(BUTTON_INPUT_MODE, DEBOUNCE_INTERVAL_MS);
RFModule radio;

CRGB leds[LED_COUNT];
IRrecv ir(IR_RECV_PIN);
IRsend ir_send;
IRSlot ir_play_slot;
decode_results ir_results;

uint8_t module = RF_MODULE;
uint8_t slot = 0;

void ir_learn(uint8_t slot);

void ir_play(uint8_t slot);

void (*learn_routines[])(uint8_t slot) = {&ir_learn, NULL, NULL};

void (*play_routines[])(uint8_t slot) = {&ir_play, NULL, NULL};

void set_leds() {
    for (int i = 0; i < MODULE_COUNT; i++) {
        leds[i] = module == i ? CRGB::DarkGoldenrod : CRGB::Black;
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
    FastLED.setBrightness(5);

    ir.enableIRIn();
    set_leds();
}

void loop() {
    Buttons::button_type read_button = buttons.currently_pressed();
    if (read_button != Buttons::NONE) {
        DEBUG_PRINT("Read button: ");
        DEBUG_PRINTLN(read_button);

        switch (read_button) {
            case Buttons::MODE:
                increment_switchable(&module, MODULE_COUNT);
                DEBUG_PRINT("Switched to module #");
                DEBUG_PRINTLN(module);
                set_leds();
                break;
            case Buttons::SLOT:
                increment_switchable(&slot, SLOT_COUNT);
                DEBUG_PRINT("Switched to slot #");
                DEBUG_PRINT(slot);
                DEBUG_PRINT(" within module #");
                DEBUG_PRINTLN(module);
                set_leds();
                break;
            case Buttons::LEARN:
                if (learn_routines[module]) {
                    learn_routines[module](slot);
                }
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
        set_leds();
        radio = RFModule();
    }
}

void ir_learn(uint8_t slot) {
    while (true) {
        if (ir.decode(&ir_results)) {
            IRSlot irslot;
            irslot.used = true;
            irslot.value = ir_results.value;
            irslot.address = ir_results.address;
            irslot.protocol = ir_results.decode_type;
            bool known = false;
            for (int i = 0; i < SUPPORTED_IR_PROTOCOLS_LEN; ++i) {
                if (irslot.protocol == SUPPORTED_IR_PROTOCOLS[i]) {
                    known = true;
                    break;
                }
            }
            if (known) {
                DEBUG_PRINT("Saving into IR slot: ");
                DEBUG_PRINT(slot);
                DEBUG_PRINT(" value: ");
                DEBUG_PRINTLN(irslot.value);
                eeprom_write_ir_slot(slot, &irslot);
            }
            ir.resume();
            return;
        }
    }
}

void ir_play(uint8_t slot) {
    eeprom_read_ir_slot(slot, &ir_play_slot);
    uint32_t val = ir_play_slot.value;
    uint32_t addr = ir_play_slot.address;
    uint32_t len = ir_play_slot.length;

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


void increment_switchable(uint8_t *variable, int max_count) {
    (*variable) = ((*variable) + 1) % max_count;
}


