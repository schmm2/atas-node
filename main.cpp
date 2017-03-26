#include "main.h"


int main(){
	printf("atas-service started\n");

	Atasgps* atasgps = new Atasgps();
	
	/* connect to gpsd */
	if(atasgps->connect() == 0){
		
		int i;	
		while(1){
			gpsLocation = atasgps->getLocation();
		
			for (i=0;i < (sizeof (gpsLocation) /sizeof (gpsLocation[0]));i++) {
    				printf("%lf\n",gpsLocation[i]);
			}
			sleep(sleeptime);
		}
	}			
}
