#include "potmeter.h"

/*-------------------EVENT HANDLERS-------------------------*/

static void CCONV onPotVoltageChange(PhidgetVoltageInputHandle ch, void * ctx, double voltage) {
	printf("Voltage: %lf\n", voltage);
}

static void CCONV onPotAttach(PhidgetHandle ch, void * ctx) {
	printf("Potentiometer attached!\n");
}

static void CCONV onPotDetach(PhidgetHandle ch, void * ctx) {
	printf("Potentiometer detached!\n");
}

static void CCONV onPotError(PhidgetHandle ch, void * ctx, Phidget_ErrorEventCode code, const char * description) {
	printf("Description: %s\n", description);
	printf("----------\n");
}

static void CCONV onPotVoltageRatioChange(PhidgetVoltageRatioInputHandle ch, void * ctx, double voltageRatio) {
	printf("VoltageRatio: %lf\n", voltageRatio);
}


/*------------------- FUNCTIONS -------------------------*/

int init_potentiometer(PhidgetVoltageRatioInputHandle* potHandle, int channelNumber) {

	// Create handle
	PhidgetVoltageRatioInput_create(potHandle);

	// Initialize channel
	retPot = Phidget_setChannel((PhidgetHandle)*potHandle, channelNumber);
	if(checkForErrorCode(retPot)!=0){
        printf("Error initializing potmeter phidget.\n");
    };

	// Initialize event handlers
	PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(*potHandle, onPotVoltageRatioChange, NULL);
	Phidget_setOnAttachHandler((PhidgetHandle)*potHandle, onPotAttach, NULL);
	Phidget_setOnDetachHandler((PhidgetHandle)*potHandle, onPotDetach, NULL);
	Phidget_setOnErrorHandler((PhidgetHandle)*potHandle, onPotError, NULL);

	return 0;
};

int run_potentiometer(PhidgetVoltageRatioInputHandle* potHandle) {

	retPot = Phidget_openWaitForAttachment((PhidgetHandle)*potHandle, 5000);
	if(checkForErrorCode(retPot)!=0){
        printf("Error attatching potmeter phidget.\n");
    };

	getchar();

	return 0;
};

int close_potentiometer(PhidgetVoltageRatioInputHandle* potHandle) {

	retPot = Phidget_close((PhidgetHandle)*potHandle);
	if(checkForErrorCode(retPot)!=0){
        printf("Error closing potmeter phidget.\n");
    };

	PhidgetVoltageRatioInput_delete(potHandle);
}
