#include "ataslora.h"
using namespace std;

// Pin mapping
const lmic_pinmap lmic_pins = { 
    .nss  = RF_CS_PIN,
    .rxtx = LMIC_UNUSED_PIN,
    .rst  = RF_RST_PIN,
    .dio  = {LMIC_UNUSED_PIN, LMIC_UNUSED_PIN, LMIC_UNUSED_PIN},
};


int Ataslora::init(){
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

}

void Ataslora::sendData(uint8_t data[]) {
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        printf("OP_TXRXPEND, not sending\n");
    } else {
        digitalWrite(RF_LED_PIN, HIGH);
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, data, sizeof(data)-1, 0);
        printf("Packet queued\n");
    }

    os_runloop_once();
}


/* Event Handler for oslmic library */
void onEvent (ev_t ev) {
    switch(ev) {
        case EV_SCAN_TIMEOUT:
            printf("EV_SCAN_TIMEOUT\n");
        break;
        case EV_BEACON_FOUND:
            printf("EV_BEACON_FOUND\n");
        break;
        case EV_BEACON_MISSED:
            printf("EV_BEACON_MISSED\n");
        break;
        case EV_BEACON_TRACKED:
            printf("EV_BEACON_TRACKED\n");
        break;
        case EV_JOINING:
            printf("EV_JOINING\n");
        break;
        case EV_JOINED:
            printf("EV_JOINED\n");
            digitalWrite(RF_LED_PIN, LOW);
            // Disable link check validation (automatically enabled
            // during join, but not supported by TTN at this time).
            LMIC_setLinkCheckMode(0);
        break;
        case EV_RFU1:
            printf("EV_RFU1\n");
        break;
        case EV_JOIN_FAILED:
            printf("EV_JOIN_FAILED\n");
        break;
        case EV_REJOIN_FAILED:
            printf("EV_REJOIN_FAILED\n");
            printf("EV_REJOIN_FAILED\n");
        break;
        case EV_TXCOMPLETE:
            printf("EV_TXCOMPLETE (includes waiting for RX windows)\n");
            if (LMIC.txrxFlags & TXRX_ACK)
              printf("Received ack\n");
            if (LMIC.dataLen) {
              printf("Received %d bytes of payload\n", LMIC.dataLen);
            }
            digitalWrite(RF_LED_PIN, LOW);
	break;
        case EV_LOST_TSYNC:
            printf("EV_LOST_TSYNC\n");
        break;
        case EV_RESET:
            printf("EV_RESET\n");
        break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            printf("EV_RXCOMPLETE\n");
        break;
        case EV_LINK_DEAD:
        printf("EV_LINK_DEAD\n");
        break;
        case EV_LINK_ALIVE:
            printf("EV_LINK_ALIVE\n");
        break;
        default:
            printf("Unknown event\n");
        break;
    }
}

void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
void os_getDevEui (u1_t* buf) { getDevEuiFromMac(buf); }
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}
