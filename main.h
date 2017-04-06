#include "atasgps.h"
#include "ataslora.h"
#include <unistd.h>
#include <string>
#include <sstream>
#include <iostream>  

using namespace std;

Ataslora* ataslora;
Atasgps* atasgps;

array<double,2>  gpsLocation;
int sleeptime = 20; 
int atasLoraState = 0;

static osjob_t sendDataJob;
