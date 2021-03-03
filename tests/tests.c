#include "phidget22.h"
#include <stdio.h>
#include <unistd.h> //For sleeps 
#include <time.h>

int test_potentiometer(PhidgetHandle *potHandle);
int test_servo(PhidgetHandle *servoHandle);

static void CCONV onVoltageChange(PhidgetVoltageInputHandle ch, void * ctx, double voltage) {
	printf("Voltage: %lf\n", voltage);
}

static void CCONV onAttach(PhidgetHandle ch, void * ctx) {
	printf("Attach!\n");
}

static void CCONV onDetach(PhidgetHandle ch, void * ctx) {
	printf("Detach!\n");
}

static void CCONV onError(PhidgetHandle ch, void * ctx, Phidget_ErrorEventCode code, const char * description) {
	printf("Description: %s\n", description);
	printf("----------\n");
}

static void CCONV onVoltageRatioChange(PhidgetVoltageRatioInputHandle ch, void * ctx, double voltageRatio) {
	printf("VoltageRatio: %lf\n", voltageRatio);
}

int main(void) {

    PhidgetVoltageRatioInputHandle potHandle;
    test_potentiometer(potHandle);

};


int test_potentiometer(PhidgetHandle *potHandle) {

    PhidgetReturnCode retPot;
    PhidgetReturnCode retPotError;

    PhidgetVoltageRatioInput_create(potHandle);


    return 0;
};

int test_servo(PhidgetHandle *servoHandle) {
    return 0;
};