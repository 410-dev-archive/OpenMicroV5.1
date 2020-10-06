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
public:
	int runMotor(motor[] motorObjects, int timeInMillisecond) {
		try{
			for(int indexOfObjects = 0; indexOfObjects < motorObjects.length; indexOfObjects++) {
				motorObjects[indexOfObjects].spin(directionType::fwd, ctl.Axis3.value(),velocityUnits::pct);
			}
			task::sleep(timeInMillisecond);
			return 0;
		}catch(Exception e) {
			return 1;
		}
	}
}