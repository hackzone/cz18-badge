#include <RCSwitch.h>
RCSwitch rcs = RCSwitch();

class RFModule {
public:
	void radioRX();
	void radioTXpayload(char*);
  void radioTXcommand(char*, char*);
  RFModule();
};
RFModule::RFModule(){
	//9k6 is advised max for cheap modules, possibly go lower
  
  rcs.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}


void RFModule::radioRX() {
  //Serial.println("radioRX");
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
  delay(500);
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


