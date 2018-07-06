#ifndef __BUTTONS_H_INCLUDED__
#define __BUTTONS_H_INCLUDED__

#include "common.h"

class Buttons {
  public:
    const static int BUTTON_COUNT = 4;
    const static int BUTTON_PINS[BUTTON_COUNT];
    
    enum button_type {
      MODE = 0,
      SLOT,
      LEARN,
      PLAY,
      NONE = -1
    };
    
    Buttons(int pin_mode, int debounce_ms, bool open_high);
    void setup();
    button_type currently_pressed();
    
  private:
    const static int SWITCH_READ_COUNT;

    bool read_update_button(int bindex);
    bool read_button_state(int bindex);

    int pin_mode;
    int debounce_ms;
    bool open_high;
    bool button_state[BUTTON_COUNT];
    int last_update[BUTTON_COUNT];
};

#endif
