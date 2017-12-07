#include "ataslora.h"
using namespace std;

void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI,8); }
void os_getDevKey (u1_t* buf) { memcpy_P(buf, APPKEY, 16);}

// Pin mapping
const lmic_pinmap lmic_pins = { 
    .nss  = RF_CS_PIN,
    .rxtx = LMIC_UNUSED_PIN,
    .rst  = RF_RST_PIN,
    .dio  = {LMIC_UNUSED_PIN, LMIC_UNUSED_PIN, LMIC_UNUSED_PIN},
};


void Ataslora::setTxPower(int powerlevel){
	int dr = DR_SF12;
	switch(powerlevel) {
   		case 12:
      		dr = DR_SF12;
		break;
		case 11:
		dr = DR_SF11;
		break;
		case 10:
                dr = DR_SF10;
		break;
		case 9:
                dr = DR_SF9;
      		break; 
		case 8:
                dr = DR_SF8;
		break;
		case 7:
                dr = DR_SF7;
		break;
		default:
		dr = DR_SF7;
		break;
	}
	// DR_SF12 = 0, DR_SF11 = 1 ...
	printf("TX Spreadingfactor wil be set to SF%d\n",(12-dr));
	LMIC_setDrTxpow(dr, 14);
}

void Ataslora::setState(int newState){
        state = newState;
}


int Ataslora::getState(){
	return state;
}

int Ataslora::init(int powerlevel){
	printf("ataslora: Keys\n");
	printKeys();

	 // Init GPIO bcm
    	if (!bcm2835_init()) {
        	fprintf( stderr, "bcm2835_init() Failed\n\n" );
        	return 1;
    	}

	// Light off on board LED
	pinMode(RF_LED_PIN, OUTPUT);
    	digitalWrite(RF_LED_PIN, HIGH);

	// LMIC init
    	os_init();
    	// Reset the MAC state. Session and pending data transfers will be discarded.
    	LMIC_reset();

	// set powerlevel
	sf = powerlevel;
}

void Ataslora::setData(osjob_t* job, string messageString) {
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        printf("OP_TXRXPEND, not sending\n");
    } else {
        digitalWrite(RF_LED_PIN, HIGH);
	
	this->setTxPower(sf);

	printf("ataslora: datarate");
	printf("%s",LMIC.datarate);
	
	// convert string -> unsigned char *
	unsigned char* message = (unsigned char*)messageString.c_str();
        LMIC_setTxData2(1, message, messageString.length(), 0);
        printf("ataslora: packets queued\n");
    }
}
