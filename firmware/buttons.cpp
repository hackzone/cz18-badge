#include "buttons.h"

const uint8_t Buttons::BUTTON_PINS[BUTTON_COUNT] { A2, A3, A6, A7 };

const uint8_t Button::SWITCH_READ_COUNT = 15;

Button::Button() : Bounce()
{
  
}

bool Button::readCurrentState()
{
  if(this->pin == Buttons::BUTTON_PINS[0] || this->pin == Buttons::BUTTON_PINS[1])
  {
      return digitalRead(this->pin);
  }
  
  uint16_t rmax = 0, rmin = 1024;
  uint16_t cur = 0;
  
  for(int16_t i = 0; i < Button::SWITCH_READ_COUNT; i++)
  {
      cur = analogRead(this->pin);
      if (cur > rmax) {
        rmax = cur;
      }
      if (cur < rmin) {
        rmin = cur;
      }
      // Artificially delay the process so as to get better readings
      delayMicroseconds(150);
  }
  
  return (rmin == 0) && (rmax <= 10);
}


Buttons::Buttons(int debounce_ms) :
        debounce_ms(debounce_ms)
{
}

void Buttons::setup()
{
  for(int32_t i = 0; i < Buttons::BUTTON_COUNT; ++i)
  {
    if(i < 2) {
      this->buttons[i].attach(Buttons::BUTTON_PINS[i], INPUT_PULLUP);
      this->buttons[i].interval(this->debounce_ms);
    } else {
      this->buttons[i].attach(Buttons::BUTTON_PINS[i], INPUT);
      this->buttons[i].interval(this->debounce_ms);
    }
  }
}

Buttons::button_type Buttons::currently_pressed()
{
  int output = static_cast<int>(Buttons::NONE);
  
  for (int i = 0; i < Buttons::BUTTON_COUNT; ++i)
  {
    if (this->buttons[i].update() && this->buttons[i].read())
    {  
      if (output != (int)Buttons::NONE) 
      {
        return Buttons::NONE;
      }
      
      output = i;
    }
  }
  
  return static_cast<Buttons::button_type>(output);
}

