## About the journal
This is just a personal journal created in order to keep track of the process continuously, express thoughts and write down useful solutions and tricks. Hopefully it might be of help for others later on.

## Installing phidget

 - Installed phidget22 directly into the resources folder. If it works it might be a beautiful solution. However, there might be some potential conflicts with the fidget control panel when it tries to fetch its own libraries. In such a case then
 1. Try to change the environmental variables of the fidget control panel
 2. If this is not possible, perhaps due to not being directly accessible, then revert and do it the traditional way. 

#### Test - phidget library include ok
Result: Success!

I had a major problem with the main file not being able to compile due to not finding the header files for phidget. Solution:
- https://github.com/microsoft/vscode-cpptools/issues/4417

The solution was to include "-I ${workspaceFolder}/resources/phidget" as a command line argument in the compiler. This has to be manually done whenever running the program on a new computer however. 

## Plan 12.01.2021

Initially, I think a good approach is to 

1. Connect to the potentiometer and make sure that data is read accurately. This includes implementation of the necessary code (properly structured) and testing. 

2. Connect to the servo and test. 

3. Implement the PID control

## Proposed solution for the potentiometer

There are two approaches to reading the potentiometer, and each of them might have their drawbacks and advantages. 

1. Create an event-change function with a given data interval that tells the rest of the code to run upon changes in voltage given from the potentiometer. 
2. In the while-loop, just read the position of the potentiometer for every iteration without an event-change function.

I initially think the second option is the best one.

## Including headers
One thing I have always found confusing is how the #include "header.h" should be structured. Should your self-made header files include all the standard libraries? Should the c-file include those instead? This was well answered on this site: https://www.learncpp.com/cpp-tutorial/header-files/

Another useful thing i learned there was the order of your includes. Your should order them like this
1. Self-made headers
2. Third-party libraries
3. Standard libraries

## Realization
I realise that I am structuring my program such that each component is not an object, even though I am treating it as one. This makes the programming a little bit cronky, but it should work in the end. How can I structure it better? 

## Problem creating handle
Status: unsolved

C:/Users/Bruker/OneDrive - NTNU/Coding/MDL-Dynamic-Positioning/src/main.c:44: undefined reference to `__imp_PhidgetVoltageRatioInput_create'
collect2.exe: error: ld returned 1 exit status

The solution might be here somewhere: 
- https://stackoverflow.com/questions/15726931/c-qt-undefined-reference-to-imp
- https://stackoverflow.com/questions/37660415/undefined-reference-to-imp-using-mingw

We're getting closer! The solution is hinted to here:
https://www.phidgets.com/docs/Troubleshooting_Common_Issues#Windows

SOLVED!
The solution was found here: https://stackoverflow.com/questions/53270833/g-linking-stage-l-flag-not-working

When specifying the library you have to first use the -L-flag, then the l-flag. 