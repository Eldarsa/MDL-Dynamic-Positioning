#include "potmeter.h"

int checkForErrorCode(PhidgetReturnCode ret) {

    PhidgetReturnCode errorCode;
    if (ret != EPHIDGET_OK) {
        const char * errorString;
        char errorDetail[100];
        size_t errorDetailLen = 100;
        Phidget_getLastError(&errorCode, &errorString, errorDetail, &errorDetailLen);
		printf("Error (%d): %s\n", errorCode, errorString);
		return 1;
	}

    return 0;
}

int getArrowInput() {
    
    if (_getch() == '\033') { // if the first value is esc
        _getch(); // skip the [
        switch(_getch()) { // the real value
        case 'A':
            printf("A");
            return 1;
        case 'B':
            // code for arrow down
            printf("B");
            return 2;
        case 'C':
            // code for arrow right
            printf("B");
            return 3;
        case 'D':
            // code for arrow left
            printf("B");
            return 4;
        }
    }else{
        return _getch();
    };
};