// Atas Modules
#include "atasgps.h"
#include "ataslora.h"
#include "atassound.h"

#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>  

using namespace std;

// Lora
Ataslora* ataslora;
static osjob_t sendDataJob;
int txInterval = 20; 

// GPS
Atasgps* atasgps;
array<double,2>  gpsLocation;

// Sound
Atassound* atassound;

int buttonpressed = 0;
