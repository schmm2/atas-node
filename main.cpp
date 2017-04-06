#include "main.h"


int main(){
	printf("atas-service started\n");

	atasgps = new Atasgps();
	ataslora = new Ataslora();
	
	ataslora->init();

	/* connect to gpsd */
	if(atasgps->connect() == 0){		
		while(1){
			// 0, latitude | 1, longitude
			gpsLocation = atasgps->getLocation();
		
			// convert
			string longitude = to_string(gpsLocation[0]);
			string latitude = to_string(gpsLocation[1]);

			// build string 
			ostringstream oss;
			oss << "longitude: " << longitude;
			string message = oss.str();
			
			// build message -> int array
			uint8_t dataArray[] = "TESTMESSAGE!";
//			strcpy( (char*) dataArray, message ); 

			// set data to be send over lora
			ataslora->setData(&sendDataJob, dataArray, sizeof(dataArray));
		
			// run 
			while(ataslora->getState() == 0){
				os_runloop_once();
			}		

			sleep(sleeptime);
		}
	}			
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

