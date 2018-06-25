
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

#include <Arduino.h>

#define DEBUG 1

#if DEBUG
#  define DEBUG_PRINT(...) Serial.print(__VA_ARGS__);
#  define DEBUG_PRINTLN(...) Serial.println(__VA_ARGS__);
#else
#  define DEBUG_PRINT(...)
#  define DEBUG_PRINTLN(...)
#endif

