#ifndef POTMETER
#define POTMETER

#include "utils.h"
#include "phidget22.h"
#include <stdio.h>

PhidgetReturnCode retPot;
PhidgetReturnCode errorCode;

static void CCONV onPotVoltageChange(PhidgetVoltageInputHandle ch, void * ctx, double voltage);
static void CCONV onPotAttach(PhidgetHandle ch, void * ctx);
static void CCONV onPotDetach(PhidgetHandle ch, void * ctx);
static void CCONV onPotError(PhidgetHandle ch, void * ctx, Phidget_ErrorEventCode code, const char * description);
static void CCONV onPotVoltageRatioChange(PhidgetVoltageRatioInputHandle ch, void * ctx, double voltageRatio);

int init_potentiometer(PhidgetVoltageRatioInputHandle* potHandle, int channelNumber);
int run_potentiometer(PhidgetVoltageRatioInputHandle* potHandle);
int close_potentiometer(PhidgetVoltageRatioInputHandle* potHandle);

#endif