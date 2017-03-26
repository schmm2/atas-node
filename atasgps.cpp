#include "atasgps.h"


array<double,2> Atasgps::getLocation(){
	/* timoeut 2sec */
        if (gps_waiting (&gps_data, 2000000)) {        
                if ((connectionstate= gps_read(&gps_data)) == -1) {
                        printf("error occured reading gps data. code: %d, reason: %s\n", connectionstate, gps_errstr(connectionstate));
                } else {
                        /* Check if GPS module has established a link to the satelites */
                        if((gps_data.status == STATUS_FIX) && 
                        (gps_data.fix.mode == MODE_2D || gps_data.fix.mode == MODE_3D) &&
                        !isnan(gps_data.fix.longitude) &&
                        !isnan(gps_data.fix.latitude)){
                                printf("latitude: %f, longitude: %f \n",gps_data.fix.latitude, gps_data.fix.longitude);
				/* Store location */	
                                location = {gps_data.fix.latitude, gps_data.fix.longitude};                             
				return location;
                        }else{
                                // no data recieved from gpsd
                        	return location;
			}                               
                }
        }
}

int Atasgps::connect(){
	printf("atas-gps starts...\n"); 

        /* connect to gpsd deamon  */
        if ((connectionstate = gps_open(SERVER, PORT, &gps_data)) == -1){
                /* error function */ 
                printf("error: code: %d, reason: %s\n", connectionstate, gps_errstr(connectionstate));
                return -1;
        }else{
                printf("gpsd connection established\n");
		/* open data stream */
        	gps_stream(&gps_data, WATCH_ENABLE | WATCH_JSON, NULL);
		return 0;
        }
}

int Atasgps::close(){
	/* Close conection */
        gps_stream(&gps_data, WATCH_DISABLE, NULL);
        gps_close (&gps_data);
        return 0; 
}
