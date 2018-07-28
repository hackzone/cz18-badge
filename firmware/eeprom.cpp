//
// Created by Tom on 14/07/2018.
//

#include "eeprom.h"

uint16_t get_badge_id() {
    return eeprom_read_word(ID_EEPROM_ADDR);
}

uint32_t eeprom_slot_address(int module, int slot)
{
    uint32_t address = SLOT_EEPROM_ADDR_START;
    switch(module)
    {
        case IR_MODULE:
            address += sizeof(IRSlot) * slot;
            break;
        case RF_MODULE:
            address += ((sizeof(IRSlot) * 4) + (sizeof(RFSlot) * slot));
            break;
        default:
            address = (uint32_t)0xffffffff;
            break;
    }
    return address;
}

uint8_t eeprom_read_byte(int address)
{
    return (uint8_t)EEPROM.read(address);
}

uint16_t eeprom_read_word(int address)
{
    uint16_t ret = (eeprom_read_byte(address) & 0xFF);
    ret = (uint16_t)((ret << 8) | (eeprom_read_byte(address + 1) & 0xFF));
    return ret;
}

uint32_t eeprom_read_dword(int address)
{
    uint32_t ret = (eeprom_read_word(address) & 0xFFFF);
    ret = (uint32_t)((ret << 16) | (eeprom_read_word(address + 2) & 0xFFFF));
    return ret;
}

void eeprom_read_ir_slot(int slot_index, IRSlot * slot)
{
    uint32_t address = eeprom_slot_address(IR_MODULE, slot_index);
    slot->used = (bool)eeprom_read_byte(address);
    slot->protocol = eeprom_read_word(address + 1);
    slot->address = eeprom_read_dword(address + 3);
    slot->length = eeprom_read_dword(address + 7);
    slot->value = eeprom_read_dword(address + 11);
}

void eeprom_read_rf_slot(int slot_index, RFSlot * slot)
{
    uint32_t address = eeprom_slot_address(RF_MODULE, slot_index);
    slot->used = (bool)eeprom_read_byte(address);
    slot->protocol = (uint16_t)eeprom_read_word(address + 1);
    slot->length = (uint16_t)eeprom_read_word(address + 3);
    slot->command_value = (int32_t)eeprom_read_dword(address+7);
}

void eeprom_write_byte(int address, uint8_t value) {
    EEPROM.write(address, (value & 0xFF));
}

void eeprom_write_word(int address, uint16_t value) {
    eeprom_write_byte(address, ((value >> 8) & 0xFF));
    eeprom_write_byte(address + 1, (value & 0xFF));
}

void eeprom_write_dword(int address, uint32_t value) {
    eeprom_write_word(address, ((value >> 16) & 0xFFFF));
    eeprom_write_word(address + 2, (value & 0xFFFF));
}

void eeprom_write_ir_slot(int slot_index, IRSlot * slot) {
    uint32_t address = eeprom_slot_address(IR_MODULE, slot_index);
    eeprom_write_byte(address, slot->used);
    eeprom_write_word(address + 1, slot->protocol);
    eeprom_write_dword(address + 3, slot->address);
    eeprom_write_dword(address + 7, slot->length);
    eeprom_write_dword(address + 11, slot->value);
}

void eeprom_write_rf_slot(int slot_index, RFSlot *slot) {
    uint32_t address = eeprom_slot_address(RF_MODULE, slot_index);
    eeprom_write_byte(address, slot->used);
    eeprom_write_word(address + 1, slot->protocol);
    eeprom_write_word(address + 3, slot->length);
    eeprom_write_dword(address + 7, slot->command_value);
}
