//
// Created by Tom on 14/07/2018.
//

#include "common.h"

uint16_t get_badge_id() {
    return eeprom_read_word(ID_EEPROM_ADDR);
}
