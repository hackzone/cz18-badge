#include <Arduino.h>
#include <FastLED.h>
#include <volume2.h>
#include <IRremoteInt.h>
#include <IRremote.h>
#include <RCSwitch.h>
#define LED_STRIP_PIN 4
#define LED_STRIP_SIZE 10
#define IR_RECV_PIN 7
#define RC_RECV_INT 0 // Digital pin 2 == interrupt 0


/**
 * === PIN LAYOUT ===
 * IR:
 * * D3 - Transmitter
 * * D7 - Receiver
 * 
 * 433MHz RF:
 * * D8 - Transmitter
 * * D2 - Receiver
 * 
 * LED Strip:
 * * D4 - Input
 * 
 * Buzzers:
 * * D5 & D6 - Buzzer 1
 * * D9 & D10 - Buzzer 2
 * 
 * Buttons:
 * A2 - Mode switch
 * A3 - Slot select
 * A4 - Learn
 * A5 - Play
 * 
 */

// Define the array of leds
CRGB leds[LED_STRIP_SIZE];
Volume vol;
IRrecv ir_receiver(IR_RECV_PIN);
RCSwitch mySwitch;
decode_results ir_decode;
int32_t code_expect = 0xff696897;
boolean lights = true;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  LEDS.addLeds<WS2812B,LED_STRIP_PIN,RGB>(leds,LED_STRIP_SIZE);
  LEDS.setBrightness(84);
  ir_receiver.enableIRIn();
  mySwitch.enableReceive(RC_RECV_INT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int current_received = 0;
  static uint8_t hue = 0;

  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }

  for(int i = 0; i < LED_STRIP_SIZE; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }

  // Now go in the other direction.  
  for(int i = (LED_STRIP_SIZE)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(10);
  }
  
  if (ir_receiver.decode(&ir_decode)) {
    Serial.print("Received: ");
    Serial.print(ir_decode.value, HEX);
    current_received = ir_decode.value;
    Serial.println();
    ir_receiver.resume();
  }
  
  if (lights) {
    
  } else {
    
  }
}

void fadeall() { for(int i = 0; i < LED_STRIP_SIZE; i++) { leds[i].nscale8(250); } }
