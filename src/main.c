/*#################################################

Project: Dynamic positioning 
Subject: TMR4345 - Marin datalab
Author: Eldar Sandanger

###################################################
*/

#include "pid.h"
#include "potmeter.h"
#include "servo.h"

#include "phidget22.h"

#include <stdio.h>

//Define potentiometer sampling rate
#define potRate = 2 //(ms)

//Define PID parameters
#define Kp = 0.1
#define Ki = 0.1
#define Kd = 0.1
//What others do you need? 

//Serial number
const int SERIAL_NUMBER = 85753; //is this the correct number?
const int POT_CHANNEL = 3;


int main(void){

    // Create handles
    PhidgetVoltageRatioInputHandle potHandle; 
    PhidgetRCServoHandle servoHandle;

    // Initialize phidgets
    //init_potentiometer(&potHandle, POT_CHANNEL);
    init_servo(&servoHandle);

    //run_potentiometer(&potHandle);

    run_servo(&servoHandle);

    close_potentiometer(&potHandle);
    close_servo(&servoHandle);

    //Phidget_setDeviceSerialNumber((PhidgetHandle)potHandle, SERIAL_NUMBER); //Define serial number


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