/*#################################################

Project: Dynamic positioning 
Subject: TMR4345 - Marin datalab
Author: Eldar Sandanger

###################################################
*/

#include "pid.h"
#include "potmeter.h"

#include "phidget22.h"

#include <stdio.h>

//Declare static port variables
#define potIn = 0

//Define potentiometer sampling rate
#define potRate = 2 //(ms)

//Define PID parameters
#define Kp = 0.1
#define Ki = 0.1
#define Kd = 0.1
//What others do you need? 

//Serial number
const int SERIAL_NUMBER = 85753; //is this the correct number?


int main(void){

    //Return codes
    //PhidgetReturnCode res; //Should we go for a single res?  //.. or should we make one for each? 
    PhidgetReturnCode resPot;
    PhidgetReturnCode resServo; // --||--

    // Create handles
    PhidgetVoltageRatioInputHandle potHandle; //might have to use asterix in front
    PhidgetRCServoHandle servoHandle; //might have to use asterix in front

    //potHandle = setupPotentiometer()
    //servoHandle = setupServo()

    PhidgetVoltageRatioInput_create(&potHandle); //Create channel 
    PhidgetRCServo_create(&servoHandle);

    //USE THESE TO SET THE RIGHT COMMUNICATION SETTINGS
    Phidget_setDeviceSerialNumber((PhidgetHandle)potHandle, SERIAL_NUMBER); //Define serial number
    Phidget_setChannel((PhidgetHandle)potHandle, 3); //Define channel to use 
    //For more info, see: https://www.phidgets.com/docs/Addressing_Phidgets#C

    //Attach phidgets. Prompt error if failed. 
    resPot = Phidget_openWaitForAttachment((PhidgetHandle)potHandle, PHIDGET_TIMEOUT_DEFAULT);
    if (resPot != EPHIDGET_OK) {
        printf("Potentiometer failed to attach!");
        return 1; 
    };

    resServo = Phidget_openWaitForAttachment((PhidgetHandle)servoHandle, PHIDGET_TIMEOUT_DEFAULT);
    if (resServo != EPHIDGET_OK) {
        printf("Servo failed to attach!");
        return 1;
    };

    test_potentiometer(&potHandle);


    //TEST THE POTENTIOMETER HERE


    PhidgetVoltageRatioInput_delete(&potHandle);
    PhidgetRCServo_delete(&servoHandle);


    /*Program outline: 
    
    - Attach fidgets. This includes creating channels, opening and detecting attachement.

    - Create threads? One thread could read the potentiometer, another could control the servo, 
        and a third could calculate the PID? 

    - Run loop

    - Close and detach fidgets.

    */

   printf("Program successfully completed!");
   return 0;
};