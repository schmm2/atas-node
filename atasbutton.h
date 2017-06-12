#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bcm2835.h>

using namespace std;

#define BUTTON_PIN 16

class Atasbutton
{
        private:
                bool enabled = false;
                bool initialized = false;
        public:
                void init();
                bool getState();
};

