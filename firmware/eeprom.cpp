//
// Created by Tom on 14/07/2018.
//

#include "common.h"
#include "eeprom.h"

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
    return EEPROM.read(address);
}

uint16_t eeprom_read_word(int address)
{
    uint16_t ret = eeprom_read_byte(address);
    ret = (uint16_t)((ret << 8) | eeprom_read_byte(address + 1));
}

uint32_t eeprom_read_dword(int address)
{
    uint32_t ret = eeprom_read_word(address);
    ret = (uint32_t)((ret << 16) | eeprom_read_word(address + 2));
}

void eeprom_read_ir_slot(int address, IRSlot * slot)
{
    slot->used = (bool)eeprom_read_byte(address);
    for (int i = 0; i < MAX_IR_COMMAND_SIZE; ++i)
    {
        slot->command[i] = (char)eeprom_read_byte(address + 1 + i);
    }
}

void eeprom_read_rf_slot(int address, RFSlot * slot)
{
    slot->used = (bool)eeprom_read_byte(address);
    slot->command_value = (int32_t)eeprom_read_dword(address+1);
}