#ifndef POTMETER
#define POTMETER

#include "phidget22.h"
#include <stdio.h>

int connect_potmeter(int channel); //Should it take in a reference to the handler? 
int disconnect_potmeter(void); //Should it take in a reference to the handler? 

#endif