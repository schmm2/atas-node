#include <vector>
#include <gps.h>
#include <stdlib.h>
using namespace std;

#define SERVER "localhost"
#define PORT "2947"

class Atasgps
{
	private:
		int connectionstate;
		float longitude;
		float latitude;
		struct gps_data_t gps_data;
        public:
                vector<float> getLocation();
                int connect();
                int close();
};
