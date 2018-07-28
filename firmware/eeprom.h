//
// Created by Tom on 14/07/2018.
//

#ifndef FIRMWARE_EEPROM_H
#define FIRMWARE_EEPROM_H

#include <EEPROM.h>
#include "common.h"

const uint8_t ID_EEPROM_ADDR = 0;
const uint8_t SLOT_EEPROM_ADDR_START = 2;

uint16_t badge_id();

uint32_t eeprom_slot_address(int module, int slot);
uint8_t eeprom_read_byte(int address);
uint16_t eeprom_read_word(int address);
uint32_t eeprom_read_dword(int address);
void eeprom_read_ir_slot(int slot_index, IRSlot * slot);
void eeprom_read_rf_slot(int slot_index, RFSlot * slot);

void eeprom_write_byte(int address, uint8_t value);
void eeprom_write_word(int address, uint16_t value);
void eeprom_write_dword(int address, uint32_t value);
void eeprom_write_ir_slot(int slot_index, IRSlot * slot);
void eeprom_write_rf_slot(int slot_index, RFSlot * slot);

#endif //FIRMWARE_EEPROM_H
