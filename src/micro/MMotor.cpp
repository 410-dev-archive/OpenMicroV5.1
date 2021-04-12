/*

AVER Code Write Department

VEX V5 Brain Screen Controller

*/

#include "vex.h"

#include "micro/MMotor.h"

using namespace vex;
using namespace std;

controller ctl = controller();
bool motorStatus = false;

int MMotor::runMotors(motor motorObjects[], int motorCount, directionType direction, float speed) {
	motorStatus = true;
	for(int indexOfObjects = 0; indexOfObjects < motorCount; indexOfObjects++) {
		motorObjects[indexOfObjects].spin(direction, (double)speed, velocityUnits::pct);
	}
	return 0;
}

int MMotor::runSingleMotor(motor motorObject, directionType direction, float speed) {
	motorStatus = true;
	motorObject.spin(direction, (double)speed, velocityUnits::pct);
	return 0;
}

int MMotor::stopMotors(motor motorObjects[], int motorCount) {
	motorStatus = false;
	for(int indexOfObjects = 0; indexOfObjects < motorCount; indexOfObjects++) {
		motorObjects[indexOfObjects].stop();
	}
	return 0;
}

int MMotor::stopSingleMotor(motor motorObject) {
	motorObject.stop();
	motorStatus = false;
	return 0;
}