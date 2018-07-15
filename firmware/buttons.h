#ifndef __BUTTONS_H_INCLUDED__
#define __BUTTONS_H_INCLUDED__

#include "common.h"
#include <Bounce2.h>

class Button : public Bounce {
  public:
    Button();
  protected:
    bool readCurrentState() override;
  private:
    const static uint8_t SWITCH_READ_COUNT;
};

class Buttons {
  public:
    const static uint8_t BUTTON_COUNT = 4;
    const static uint8_t BUTTON_PINS[BUTTON_COUNT];

    enum button_type {
        MODE = 0,
        SLOT,
        LEARN,
        PLAY,
        NONE = -1
    };

    Buttons(int pin_mode, int debounce_ms);
    void setup();
    Buttons::button_type currently_pressed();
    
  private:
    uint8_t pin_mode;
    int debounce_ms;
    Button buttons[BUTTON_COUNT];
};

#endif
