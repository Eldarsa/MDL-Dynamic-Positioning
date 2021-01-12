/*#################################################

Project: Dynamic positioning 
Subject: TMR4345 - Marin datalab
Author: Eldar Sandanger

###################################################
*/

#include <stdio.h>
//#include "pid.h"
//#include "potmeter.h"
#include "phidget22.h"

//Declare static port variables
#define potIn = 0;
#define potOut = 0;

//Define PID parameters
#define Kp = 0
#define Ki = 0
#define Kd = 0
//What others do you need? 

//Serial number
#define SERIAL_NUMBER = 85753 //(is this correct)

int main(void){
    printf("Test library");
};