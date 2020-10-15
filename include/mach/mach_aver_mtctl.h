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

	int runMotors(motor motorObjects[], int motorCount) {
		try{
      		motorStatus = true;
			for(int indexOfObjects = 0; indexOfObjects < motorCount; indexOfObjects++) {
				motorObjects[indexOfObjects].spin(directionType::fwd);
			}
			return 0;
		}catch(exception e) {
			return 1;
		}
	}

  int runSingleMotor(motor motorObject) {
    try{
    	motorStatus = true;
    	motorObject.spin(directionType::fwd);
		return 0;
	}catch(exception e) {
		return 1;
	}
  }
  
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