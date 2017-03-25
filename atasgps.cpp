#include "atasgps.h"

vector<float> Atasgps::getLocation(){

}

int Atasgps::connect(){
	printf("atas-gps starts...\n"); 

        /* connect to gpsd deamon  */
        if ((connectionstate = gps_open(SERVER, PORT, &gps_data)) == -1){
                /* error function */ 
                printf("error: code: %d, reason: %s\n", connectionstate, gps_errstr(connectionstate));
                return EXIT_FAILURE;
        }else{
                printf("gpsd connection established\n");
        }

        /* open data stream */
        gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);

}

int Atasgps::close(){

}

/*
int main() {
	printf("atas-gps starts...\n");	
	
	int connection;
	struct gps_data_t gps_data;
	int sleeptime = 1;	

	/* connect to gpsd deamon 
	if ((connection = gps_open(SERVER, PORT, &gps_data)) == -1){
		/* error function 
    		printf("error: code: %d, reason: %s\n", connection, gps_errstr(connection));
    		return EXIT_FAILURE;
	}else{
		printf("gpsd connection established\n");
	}

	/* open data stream 
	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
	
	/* loop forever, read gps data
	while(1){
        	/* Wait to receive gps data, timeout 2s
        	if (gps_waiting (&gps_data, 2000000)) {        
			if ((connection = gps_read(&gps_data)) == -1) {
            			printf("error occured reading gps data. code: %d, reason: %s\n", connection, gps_errstr(connection));
        		} else {
				/* Check if GPS is connected
				if((gps_data.status == STATUS_FIX) && 
				(gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
				!isnan(gps_data.fix.longitude) &&
				!isnan(gps_data.fix.latitude)){
					if(sleeptime == 1) sleeptime = 15;
					printf("latitude: %f, longitude: %f \n",gps_data.fix.latitude, gps_data.fix.longitude);
				}else{
					if(sleeptime == 15) sleeptime = 1;
					printf("no data recieved from gpsd\n");
				}				
			}
        	}
		/* go to sleep for some seconds
		sleep(sleeptime);       
	}
	/* Close conection
	gps_stream(&gps_data, WATCH_DISABLE, NULL);
	gps_close (&gps_data);

	return EXIT_SUCCESS; 
}*/
