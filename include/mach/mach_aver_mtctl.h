/*

AVER Code Write Department

VEX V5 Brain Screen Controller

*/

#include "vex.h"

using namespace vex;
using namespace std;

class AEMotorControl {
private:
	
public:
  controller ctl = controller();
  bool motorStatus = false;

	int runMotor(motor motorObjects[], int motorCount, int timeInMillisecond) {
		try{
      motorStatus = true;
			for(int indexOfObjects = 0; indexOfObjects < motorCount; indexOfObjects++) {
				motorObjects[indexOfObjects].spin(directionType::fwd);
			}
			//task::sleep(timeInMillisecond);
      motorStatus = false;
			return 0;
		}catch(exception e) {
			return 1;
		}
	}

  int runSingleMotor(motor motorObject) {
    try{
    	motorStatus = true;
    	motorObject.spin(directionType::fwd);
    	//task::sleep(timeInMillisecond);
    	motorStatus = false;
  int stopMotors(motor motorObjects[], int motorCount) {
	try{
		motorStatus = false;
		for(int indexOfObjects = 0; indexOfObjects < motorCount; indexOfObjects++) {
			motorObjects[indexOfObjects].stop();
		}
		return 0;
	}catch(exception e) {
		return 1;
	}
  }

  int stopSingleMotor(motor motorObject) {
    try{
    	motorObject.stop();
		motorStatus = false;
		return 0;
	}catch(exception e) {
		return 1;
	}
  }
};