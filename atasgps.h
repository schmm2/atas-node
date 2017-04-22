#include <array>
#include <gps.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include <unistd.h>

using namespace std;

class Atasgps
{
	private:
		const char* server = "localhost";
		const char* port = "2947";
		const int decimalPlaces = 8;		
		int connectionstate;
		array<double,2> location;
		struct gps_data_t gps_data;
        public:
                array<double,2> getLocation();
                int connect();
                int close();
};
