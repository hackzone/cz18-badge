//
// Created by Tom on 25/07/2018.
//

#ifndef FIRMWARE_IR_H
#define FIRMWARE_IR_H

#include "common.h"
#include  "ir_protocols.h"

extern IRsend ir_send;
extern IRSlot ir_play_slot;
extern decode_results ir_results;

void ir_init();
bool ir_learn(uint8_t slot, bool reinit);
void ir_play(uint8_t slot);

#endif //FIRMWARE_IR_H
