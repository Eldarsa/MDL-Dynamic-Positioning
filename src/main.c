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
#define SERIAL_NUMBER = 85753 //is this correct?


int main(void){

    //Return codes
    PhidgetReturnCode res; //Should we go for a single res? 
    PhidgetReturnCode potRes; //.. or should we make one for each? 
    PhidgetReturnCode servoRes; // --||--

    // Create handles
    PhidgetVoltageRatioInputHandle potHandle; //might have to use asterix in front
    PhidgetRCServoHandle servoHandle; //might have to use asterix in front

    PhidgetVoltageRatioInput_create(&potHandle);
    PhidgetRCServo_create(&servoHandle);

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