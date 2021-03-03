#include "potmeter.h"

PhidgetReturnCode resPot;

/*-------------------EVENT HANDLERS-------------------------*/

static void CCONV onVoltageChange(PhidgetVoltageInputHandle ch, void * ctx, double voltage) {
	printf("Voltage: %lf\n", voltage);
}

static void CCONV onAttach(PhidgetHandle ch, void * ctx) {
	printf("Attach!\n");
}

static void CCONV onDetach(PhidgetHandle ch, void * ctx) {
	printf("Detach!\n");
}

/*------------------- FUNCTIONS -------------------------*/

int connect_potentiometer(PhidgetVoltageRatioInputHandle* potHandle) {

  	resPot = Phidget_openWaitForAttachment((PhidgetHandle)potHandle, PHIDGET_TIMEOUT_DEFAULT);
    if (resPot != EPHIDGET_OK) {
        printf("Potentiometer failed to attach!");
        return 1; 
    };  

	return 0;
};

int disconnect_potentiometer() {

};
