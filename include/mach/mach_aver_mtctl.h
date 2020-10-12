/*

AVER Code Write Department

VEX V5 Brain Screen Controller

*/

#include "vex.h"

using namespace vex;
using namespace std;

class AEMotorControl {
private:
	controller ctl = controller();
  bool motorStatus = false;
public:
  bool isMotorSessionRunning() {
    return motorStatus;
  }

	int runMotor(motor motorObjects[], int motorCount, int timeInMillisecond) {
		try{
      motorStatus = true;
			for(int indexOfObjects = 0; indexOfObjects < motorCount; indexOfObjects++) {
				motorObjects[indexOfObjects].spin(directionType::fwd, ctl.Axis3.value(),velocityUnits::pct);
			}
			task::sleep(timeInMillisecond);
      motorStatus = false;
			return 0;
		}catch(exception e) {
			return 1;
		}
	}
};