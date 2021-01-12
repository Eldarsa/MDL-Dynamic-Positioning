#include "potmeter.h"


//This is an event handler that 
static void CCONV onVoltageRatioChange(PhidgetVoltageRatioInputHandle ch, void * ctx, double voltageRatio) {
	printf("VoltageRatio: %lf\n", voltageRatio);
}

int connect_potentiometer() {
    
};

int disconnect_potentiometer() {

};
