#include "buttons.h"

const uint8_t Buttons::BUTTON_PINS[BUTTON_COUNT] { A2, A3, A6, A7 };

const uint8_t Button::SWITCH_READ_COUNT = 15;

Button::Button() : Bounce()
{
  
}

bool Button::readCurrentState()
{
  if(this->pin ==A2 || this->pin == A3){
    return digitalRead(this->pin);
    
  }
  for(int16_t i = 0; i < Button::SWITCH_READ_COUNT; i++)
  {
    
      if(analogRead(this->pin))
      {
        return false;
      }
    
    
  }
  
  return true;
}


Buttons::Buttons(int pin_mode, int debounce_ms) :
        pin_mode(pin_mode),
        debounce_ms(debounce_ms)
{
}

void Buttons::setup()
{
  for(int32_t i = 0; i < Buttons::BUTTON_COUNT; ++i)
  {
    if(i<2){
      this->buttons[i].attach(Buttons::BUTTON_PINS[i], INPUT_PULLUP);
      this->buttons[i].interval(this->debounce_ms);
    }else{
      this->buttons[i].attach(Buttons::BUTTON_PINS[i], this->pin_mode);
      this->buttons[i].interval(this->debounce_ms);
    }
    
  }
}

Buttons::button_type Buttons::currently_pressed()
{
  int output = (int)Buttons::NONE;
  
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
  
  return (Buttons::button_type)output;
}

