#ifndef UserInterface_h
#define UserInterface_h
#include <Arduino.h>

class UserInterface {
    public:
    static void printSys(String, String);
    static void printSysln(String, String);
    static void printErr(String, String);
    static void printErrln(String, String);
};


#endif