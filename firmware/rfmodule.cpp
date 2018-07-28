#include <RCSwitch.h>
#include "common.h"
#include "eeprom.h"

class RFModule {
public:
    void init();
	void radioRX();
	void radioTXpayload(char*);
    void radioTXcommand(char*, char*);
    RFModule();
};

RFModule::RFModule(){
	//9k6 is advised max for cheap modules, possibly go lower
}

RCSwitch rcs = RCSwitch();
RFModule radio;

void RFModule::init() {
  Serial.println("Init RF");
  digitalWrite(13, HIGH);
  rcs.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
  rcs.enableTransmit(8);
}


void RFModule::radioRX() {
  if (rcs.available()) {

    Serial.print("Received ");
    Serial.print( rcs.getReceivedValue() );
    Serial.print(" / ");
    Serial.print( rcs.getReceivedBitlength() );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( rcs.getReceivedProtocol() );

    rcs.resetAvailable();
  }
}

void RFModule::radioTXcommand(char* command, char* message){
  //TODO add time slotted sending based on mesh network node ID
  // 255 bound for now, lets test what we can do with rc switch as it is
  char payload[255];
  strcpy(payload,"start of command");
  strcat(payload,command);
  strcat(payload,"end of command");
  strcat(payload,"start of message");
  strcat(payload,message);
  strcat(payload, "end of message literal");

  radioTXpayload(payload);
}

void RFModule::radioTXpayload(char* payload) {
	rcs.disableReceive();
	rcs.enableTransmit(8);

  Serial.print("Sending ");
  Serial.println(payload);

	rcs.send(payload);
  rcs.disableTransmit();
}

void rf_init() {
    radio = RFModule();
    radio.init();
}

bool rf_learn(uint8_t slot_index, bool reinit){
    if(!rcs.available()) { return false; }

    RFSlot slot;
    slot.used = true;
    slot.protocol = rcs.getReceivedProtocol();
    slot.length = rcs.getReceivedBitlength();
    slot.command_value = rcs.getReceivedValue();

    rcs.resetAvailable();

    DEBUG_PRINT("Received ");
    DEBUG_PRINTLN(slot.command_value);

    eeprom_write_rf_slot(slot_index, &slot);
    return true;
}

void rf_play(uint8_t slot_index){
    RFSlot slot;
    eeprom_read_rf_slot(slot_index, &slot);
    rcs.setProtocol(slot.protocol);

    DEBUG_PRINT("Sending ");
    DEBUG_PRINT(slot.command_value);
    DEBUG_PRINT(" (");
    DEBUG_PRINT(slot.length);
    DEBUG_PRINTLN(")");

    rcs.send(slot.command_value, slot.length);
}