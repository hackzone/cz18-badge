//
// Created by Tom on 14/07/2018.
//

#ifndef FIRMWARE_EEPROM_H
#define FIRMWARE_EEPROM_H

#include <EEPROM.h>

uint32_t eeprom_slot_address(int module, int slot);
uint8_t eeprom_read_byte(int address);
uint16_t eeprom_read_word(int address);
uint32_t eeprom_read_dword(int address);
void eeprom_read_ir_slot(int address, struct IRSlot * slot);
void eeprom_read_rf_slot(int address, struct RFSlot * slot);

#endif //FIRMWARE_EEPROM_H
