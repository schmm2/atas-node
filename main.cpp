#include "main.h"


int main(){
	printf("atas-service started\n");

	atasgps = new Atasgps();
	ataslora = new Ataslora();
	
	ataslora->init();

	/* connect to gpsd */
	if(atasgps->connect() == 0){
		
		int i;	
		while(1){
			// 0, latitude | 1, longitude
			gpsLocation = atasgps->getLocation();
		
			/*for (i=0;i < (sizeof (gpsLocation) /sizeof (gpsLocation[0]));i++) {
    				printf("%lf\n",gpsLocation[i]);
			}*/

			// convert
			string longitude = to_string(gpsLocation[0]);
			string latitude = to_string(gpsLocation[1]);

			// build string -> byte array
			ostringstream oss;
			oss << "longitude: " << longitude;
			string message = oss.str();

			//std::cout << message << '\n';
			
			string mem = "3333";
			uint8_t *data = new uint8_t[4];
			data = mem.c_str();			

			// send data over lora
			ataslora->sendData(data);

			sleep(sleeptime);
		}
	}			
}
