/*

AVER Code Write Department

VEX V5 Brain Screen Controller

*/

#include "vex.h"

class MMotor{
public: int runMotors(vex::motor motorObjects[], int motorCount, vex::directionType direction, float speed);
public: int runSingleMotor(vex::motor motorObject, vex::directionType direction, float speed);
public: int stopMotors(vex::motor motorObjects[], int motorCount);
public: int stopSingleMotor(vex::motor motorObject);
};