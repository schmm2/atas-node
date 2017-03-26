#include <array>
#include <gps.h>
#include <stdlib.h>
#include <math.h>
#include <thread>

using namespace std;

#define SERVER "localhost"
#define PORT "2947"

class Atasgps
{
	private:
		thread readDataThread;
		int connectionstate;
		array<double,2> location;
		struct gps_data_t gps_data;
        public:
                array<double,2> getLocation();
                int connect();
                int close();
};
