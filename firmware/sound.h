//
// Created by Tom on 25/07/2018.
//

#ifndef FIRMWARE_SOUND_H
#define FIRMWARE_SOUND_H

#include "common.h"

bool sound_learn(uint8_t slot, bool reinit);
void sound_play(uint8_t slot);

#endif //FIRMWARE_SOUND_H
