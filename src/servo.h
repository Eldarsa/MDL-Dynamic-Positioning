#ifndef SERVO
#define SERVO

#include "utils.h"
#include "phidget22.h"
#include <stdio.h>
#include <unistd.h>
#include <conio.h>

PhidgetReturnCode retServo;

static void CCONV onServoAttach(PhidgetHandle ch, void * ctx);
static void CCONV onServoDetach(PhidgetHandle ch, void * ctx);
static void CCONV onServoError(PhidgetHandle ch, void * ctx, Phidget_ErrorEventCode code, const char * description);

int init_servo(PhidgetRCServoHandle *handle);
int run_servo(PhidgetRCServoHandle *handle);
int close_servo(PhidgetRCServoHandle *handle);

#endif