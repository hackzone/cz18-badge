#ifndef __BUTTONS_H_INCLUDED__
#define __BUTTONS_H_INCLUDED__

#include "common.h"
#include <Bounce2.h>

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
    int pin_mode;
    int debounce_ms;
    bool open_high;
    Bounce buttons[Buttons::BUTTON_COUNT];
};

#endif
