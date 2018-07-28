//
// Created by Tom on 25/07/2018.
//

#include "ir.h"
#include "eeprom.h"

IRrecv ir(IR_RECV_PIN);
IRsend ir_send;
IRSlot ir_play_slot;
decode_results ir_results;

void ir_init() {
    ir.enableIRIn();
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