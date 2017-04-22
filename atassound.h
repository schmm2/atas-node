#include <unistd.h>
#include <bcm2835.h>

using namespace std;

#define PWM_PIN 18
#define PWM_CHANNEL 0
#define PWM_RANGE 1024

class Atassound
{
        private:
		bool enabled = false;
		bool initialized = false;
        public:
                void enable();
                void mute();
		void init();
		bool getState();
};
