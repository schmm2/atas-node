#include "main.h"

int main(){

	printf("atas-node: started\n");

	atasgps = new Atasgps();
	ataslora = new Ataslora();
	atassound = new Atassound();

	// connect to gps
	if(atasgps->connect() == 0){

		// init ataslora module
		ataslora->init();
		atassound->init();

		while(1){
			
			atassound->enable();

			// get GPS Data
			// 0, latitude | 1, longitude
			gpsLocation = atasgps->getLocation();

			// check if we got valid gps data
			if(gpsLocation[0] == 200 & gpsLocation[1] == 200){
				// try again
				continue;
			}

			// build string 
			ostringstream oss;

			// send gps data
			if (buttonpressed == 0){
				oss << to_string(gpsLocation[0]) << "," << to_string(gpsLocation[1]);
			}
			// send gps data + alert
			else{
				oss << to_string(gpsLocation[0]) << "," << to_string(gpsLocation[1]) << "," << buttonpressed;
			}
			string message = oss.str();

			// set data to be send over lora
			ataslora->setData(&sendDataJob, message);

			// enable ataslora to send data
			ataslora->setState(0);

			// run, until the next tx succeds
			while(ataslora->getState() == 0){
				os_runloop_once();
			}

			sleep(txInterval);
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
            printf("ataslora: joining\n");
        break;
        case EV_JOINED:
            printf("ataslora: joined\n");
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
            	printf("ataslora: tx complete\n");

		if (LMIC.txrxFlags & TXRX_ACK)
	              	printf("ataslora: received ack\n");
            	if (LMIC.dataLen) {
              		printf("ataslora: received downlink message\n");
			char str[LMIC.dataLen+1];
        		str[LMIC.dataLen]='\0'; // Add terminator
        		memcpy(&str,&(LMIC.frame+LMIC.dataBeg)[0],LMIC.dataLen); 

			string downmsg(str);
			if(downmsg == "1"){
				printf("atasalarm: triger alarm\n");
			}
		}		
            	digitalWrite(RF_LED_PIN, LOW);
		ataslora->setState(1);	
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

