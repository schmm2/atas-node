
// Atas Modules
#include "atasgps.h"
#include "ataslora.h"
#include "atassound.h"
#include "atasbutton.h"
#include "inih/ini.h"
#include "inih/INIReader.h"

#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>  

using namespace std;

uint8_t inDangerzone = 0;

// Main
int version;

// Lora
Ataslora* ataslora;
static osjob_t sendDataJob;
int txInterval; 
int sf;

// GPS
Atasgps* atasgps;
array<double,2>  gpsLocation;

// Sound
Atassound* atassound;

// Button Handling
Atasbutton* atasbutton;
uint8_t buttonPressed;
