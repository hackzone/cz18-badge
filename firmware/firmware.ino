#include "common.h"
#include "buttons.h"
#include <EEPROM.h>

struct IRSlot;
struct RFSlot;
void increment_switchable(int *variable, int max_count);

/**
 * EEPROM layout
 * badge_id - word
 * 4x IRSlot
 * 4x RFSlot
 */
const int ID_EEPROM_ADDR = 0;
const int SLOT_EEPROM_ADDR_START = 2;
const int MAX_IR_COMMAND_SIZE = 100;

uint16_t badge_id();
uint32_t eeprom_slot_address(int module, int slot);
uint8_t eeprom_read_byte(int address);
uint16_t eeprom_read_word(int address);
uint32_t eeprom_read_dword(int address);
void eeprom_read_ir_slot(int address, struct IRSlot * slot);
void eeprom_read_rf_slot(int address, struct RFSlot * slot);

const int SLOT_COUNT = 4;
const int MODULE_COUNT = 3;
const int RF_MODULE = 0,
          IR_MODULE = 1,
          TUNE_MODULE = 2;
          
const int DEBOUNCE_INTERVAL_MS = 15;
const int BUTTON_INPUT_MODE = INPUT;
const bool BUTTON_OPEN_HIGH = true;

Buttons buttons(BUTTON_INPUT_MODE, DEBOUNCE_INTERVAL_MS, BUTTON_OPEN_HIGH);

int module = RF_MODULE;
int slot = 0;

void setup() {
  Serial.begin(115200);
  buttons.setup();
}

void loop() {
  Buttons::button_type read_button = buttons.currently_pressed();
  if (read_button != Buttons::button_type::NONE) {
    DEBUG_PRINT("Read button: ");
    DEBUG_PRINTLN(read_button);

    switch (read_button) {
      case Buttons::button_type::MODE:
        increment_switchable(&module, MODULE_COUNT);
        slot = 0;
        DEBUG_PRINT("Switched to module #");
        DEBUG_PRINTLN(module);
        break;
      case Buttons::button_type::SLOT:
        if (module == RF_MODULE || module == IR_MODULE) {
          increment_switchable(&slot, SLOT_COUNT);
          DEBUG_PRINT("Switched to slot #");
          DEBUG_PRINT(slot);
          DEBUG_PRINT(" within module #");
          DEBUG_PRINTLN(module);
        }
        break;
      case Buttons::button_type::LEARN:
        // TODO: Learn according to selected module
        break;
      case Buttons::button_type::PLAY:
        // TODO: Play according to the selected module
        break;
      default:
        // Do nothing if unknown
        break;
    }
  }
}

void increment_switchable(int *variable, int max_count) {
  (*variable) = ((*variable) + 1) % max_count;
}

typedef struct IRSlot
{
  bool used;
  char command[MAX_IR_COMMAND_SIZE];
} IRSlot;

typedef struct RFSlot
{
  bool used;
  int32_t command_value;
} RFSlot;


uint16_t get_badge_id()
{
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

