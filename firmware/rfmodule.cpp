#include <RCSwitch.h>
RCSwitch rcs = RCSwitch();

class RFModule {
public:
	void radioRX();
	void radioTX();
  RFModule();
};
RFModule::RFModule(){
  Serial.begin(9600);
  rcs.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}
void RFModule::radioRX() {
	if (rcs.available()) {
		//Serial.println(rcs.getReceivedValue(), rcs.getReceivedBitlength(), rcs.getReceivedDelay(), rcs.getReceivedRawdata(), rcs.getReceivedProtocol());
		rcs.resetAvailable();
	}
}

void RFModule::radioTX() {
	
}


