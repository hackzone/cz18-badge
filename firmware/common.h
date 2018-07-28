
/**
   === PIN LAYOUT ===
   IR:
 * * D3 - Transmitter
 * * D7 - Receiver

   433MHz RF:
 * * D8 - Transmitter
 * * D2 - Receiver

   LED Strip:
 * * D4 - Input

   Buzzers:
 * * D5 & D6 - Buzzer 1
 * * D9 & D10 - Buzzer 2

   Buttons:
   A2 - Mode switch
   A3 - Slot select
   A6 - Learn
   A7 - Play

*/
#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>

#define DEBUG 1

#if DEBUG
#  define DEBUG_PRINT(...) Serial.print(__VA_ARGS__);
#  define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__);
#else
#  define DEBUG_PRINT(...)
#  define DEBUG_PRINTLN(...)
#endif


#define IR_MODULE 0
#define TUNE_MODULE 1
#define RF_MODULE 2

#define SLOT_COUNT 4
#define MODULE_COUNT 3


#define IR_SEND_PIN 3
#define IR_RECV_PIN 7

/**
 * EEPROM layout
 * badge_id - word
 * 4x IRSlot
 * 4x RFSlot
 */
typedef struct IRSlot {
    bool used; // 16
    uint16_t protocol; // 17
    uint32_t address; // 7
    uint32_t length; // 11
    uint32_t value; // 15
} IRSlot;

typedef struct RFSlot {
    bool used;
    uint16_t protocol;
    uint32_t length;
    int32_t command_value;
} RFSlot;

extern uint8_t module;
extern uint8_t slot;

void increment_switchable(int *variable, int max_count);

#endif
