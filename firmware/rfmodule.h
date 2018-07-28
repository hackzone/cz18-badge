#include <RCSwitch.h>
extern const uint8_t RX_OFF,RX_TIMED,RX_CONTINUOUS;

void rf_init();
bool rf_learn(uint8_t slot_index, bool reinit);
void rf_play(uint8_t slot_index);

class RFModule {

public:
	void radioRX();
	void init();
	void radioTXpayload(char*);
  	void radioTXcommand(char*, char*);
	RCSwitch rcs;

  
	uint8_t rxState;
  //TODO switchcase it and add timed handler, maybe bring it to class impl ;P
	void inline setRxState(const uint8_t param) { rxState = param; ((param == RX_OFF)?rcs.disableReceive():rcs.enableReceive()); }
	uint8_t inline getRxState() { return rxState ; }
private:
  };
