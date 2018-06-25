#include "buttons.h"

const static int Buttons::BUTTON_PINS[BUTTON_COUNT] { A2, A3, A4, A5 };

Buttons::Buttons(int pin_mode, int debounce_ms, bool open_high) :
        pin_mode(pin_mode),
        debounce_ms(debounce_ms),
        open_high(open_high)
{
  
}

void Buttons::setup()
{
  for(int32_t i = 0; i < Buttons::BUTTON_COUNT; ++i)
  {
    this->buttons[i].attach(Buttons::BUTTON_PINS[i], this->pin_mode);
    this->buttons[i].interval(this->debounce_ms);
  }
}

Buttons::button_type Buttons::currently_pressed()
{
  int output = (int)Buttons::button_type::NONE;
  
  for (int i = 0; i < Buttons::BUTTON_COUNT; ++i) {
    // The button is pressed if the value of read is the false when it is open high or true when it is open low
    // and it has been updated.
    if (this->buttons[i].update() && (this->open_high != this->buttons[i].read())) {

      if (output != (int)Buttons::button_type::NONE) {
        // Already read a button, so we have two buttons pressed at the same time
        // for now, this is undefined behaviour.
        return Buttons::button_type::NONE;
      }

      output = i;
    }
  }

  return (Buttons::button_type)output;
}

