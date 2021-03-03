#include "phidget22.h"
#include <stdio.h>
#include <unistd.h> //For sleeps 
#include <time.h>

int test_potentiometer(PhidgetVoltageRatioInputHandle *potHandle);
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

//************* MAIN ***************
    
int main(void) {

    PhidgetVoltageRatioInputHandle potHandle;
    test_potentiometer(&potHandle);

};


int test_potentiometer(PhidgetVoltageRatioInputHandle *potHandle) {

    PhidgetReturnCode retPot;
    PhidgetReturnCode retPotError;
    const char * errorString;
	char errorDetail[100];
	size_t errorDetailLen = 100;

    PhidgetVoltageRatioInput_create(potHandle);

    retPot = Phidget_setChannel((PhidgetHandle)*potHandle, 3);
	if (retPot != EPHIDGET_OK) {
        printf("Hello world\n");
        Phidget_getLastError(&retPotError, &errorString, errorDetail, &errorDetailLen);
		printf("Error (%d): %s\n", retPotError, errorString);
		exit(1);
	}

    PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(*potHandle, onVoltageRatioChange, NULL);
	Phidget_setOnAttachHandler((PhidgetHandle)*potHandle, onAttach, NULL);
	Phidget_setOnDetachHandler((PhidgetHandle)*potHandle, onDetach, NULL);
	Phidget_setOnErrorHandler((PhidgetHandle)*potHandle, onError, NULL);

    retPot = Phidget_openWaitForAttachment((PhidgetHandle)*potHandle, 5000);
	if (retPot != EPHIDGET_OK) {
		Phidget_getLastError(&retPotError, &errorString, errorDetail, &errorDetailLen);
		printf("Error (%d): %s", retPotError, errorString);
		exit(1);
	}

    getchar();

    printf("SUCCESS!!\n");

    return 0;
};

int test_servo(PhidgetHandle *servoHandle) {
    return 0;
};