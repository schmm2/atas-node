#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bcm2835.h>

using namespace std;

#define BUTTON_PIN 16

class Atasbutton
{
        private:
                bool initialized = false;
        public:
                void init();
                uint8_t getState();
};

