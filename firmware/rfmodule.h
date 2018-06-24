extern const uint8_t RX_OFF,RX_TIMED,RX_CONTINUOUS;
class RFModule {

public:
	void radioRX();
	void radioTX();

  
	uint8_t rxState;
	void inline setRxState(const uint8_t param) { rxState = param; }
	uint8_t inline getRxState() { return rxState ; }
private:
  };
