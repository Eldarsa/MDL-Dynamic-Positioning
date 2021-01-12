## Installing phidget

 - Installed phidget22 directly into the resources folder. If it works it might be a beautiful solution. However, there might be some potential conflicts with the fidget control panel when it tries to fetch its own libraries. In such a case then
 1. Try to change the environmental variables of the fidget control panel
 2. If this is not possible, perhaps due to not being directly accessible, then revert and do it the traditional way. 

#### Test - phidget library include ok
Result: Success!

I had a major problem with the main file not being able to compile due to not finding the header files for phidget. Solution:
- https://github.com/microsoft/vscode-cpptools/issues/4417

The solution was to include "-I ${workspaceFolder}/resources/phidget" as a command line argument in the compiler. This has to be manually done whenever running the program on a new computer however. 

## 