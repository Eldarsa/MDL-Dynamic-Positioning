#include "servo.h"

/*--------------- EVENT HANDLERS ----------------------*/

static void CCONV onServoAttach(PhidgetHandle ch, void * ctx) {
    printf("Servo attached!\n");
};

static void CCONV onServoDetach(PhidgetHandle ch, void * ctx) {
    printf("Servo detached!\n");
};

static void CCONV onServoError(PhidgetHandle ch, void * ctx, Phidget_ErrorEventCode code, const char * description) {
    printf("Description: %s\n", description);
	printf("----------\n");
};

void CCONV positionChangeHandler(PhidgetRCServoHandle ch, void *ctx, double position) {
	printf("ServoPosition %v", position);
};

/*-------------------- FUNCTIONS ----------------------*/

int init_servo(PhidgetRCServoHandle *handle) {

    PhidgetRCServo_create(handle);

    retServo = PhidgetRCServo_setOnPositionChangeHandler(*handle, positionChangeHandler, NULL);
	if(checkForErrorCode(retServo)!=0){
        printf("Error initializing servo phidget.\n");
    };

    Phidget_setOnAttachHandler((PhidgetHandle)*handle, onServoAttach, NULL);
	Phidget_setOnDetachHandler((PhidgetHandle)*handle, onServoDetach, NULL);
	Phidget_setOnErrorHandler((PhidgetHandle)*handle, onServoError, NULL);

    return 0;
};

int run_servo(PhidgetRCServoHandle *handle) {

    retServo = Phidget_openWaitForAttachment((PhidgetHandle)*handle, PHIDGET_TIMEOUT_DEFAULT);
	if(checkForErrorCode(retServo)!=0){
        printf("Error attatching servo phidget.\n");
    };

    int ch;
    while(ch = getArrowInput()) {
        switch(ch) {
        case 1:
            printf("1");
        case 2:
            printf("2");
        case 3:
            printf("Exiting loop");
            break;
        default:
            printf("Default");
            sleep(0.01);
            continue;
        };
    };

    return 0;
};

int close_servo(PhidgetRCServoHandle *handle) {

    retServo = Phidget_close((PhidgetHandle)*handle);
    if(checkForErrorCode(retServo)!=0){
        printf("Error closing servo phidget\n");
    };

    PhidgetRCServo_delete(handle);

    return 0;
};

/*--------------------- ACTION FUNCTIONS ---------------------------*/

void setSpeed(){

};
