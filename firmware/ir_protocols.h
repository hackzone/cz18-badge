//
// Created by khaled on 15/07/18.
//

#ifndef FIRMWARE_IR_PROTOCOLS_H
#define FIRMWARE_IR_PROTOCOLS_H

#include "common.h"
#include <IRremote.h>

const int SUPPORTED_IR_PROTOCOLS[] = {
        AIWA_RC_T501,
        DENON,
        JVC,
        LG,
        NEC,
        PANASONIC,
        RC5,
        RC6,
        SAMSUNG,
        SONY,
        WHYNTER
};

const int SUPPORTED_IR_PROTOCOLS_LEN = (sizeof(SUPPORTED_IR_PROTOCOLS) / sizeof(int));

#endif //FIRMWARE_IR_PROTOCOLS_H
