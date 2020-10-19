/*

AVER Code Write Department

VEX V5 Brain Remote Controller

*/

#include "vex.h"
#include <string>

#include <fstream>
#include <iostream>

#include "hardwareinfo.h"
#include "mach/mach_aver_srutil.h"

using namespace vex;
using namespace std;

//#define sdcard vex::brain::sdcard

class RemoteControl {
public:
  AESensorsUtility aeutils;
  int buttonR1, buttonR2, buttonL1, buttonL2;
  int buttonX, buttonY, buttonA, buttonB;
  int buttonUp, buttonDown, buttonRight
	bool retrieve(controller Controller) {
    int value = aeutils.getShaftEncoderValue(testShaftEncoder);
    Controller.ButtonR1.pressing();
    Controller.ButtonR2.pressing();
    Controller.ButtonL1.pressing();
    Controller.ButtonL2.pressing();
    Controller.ButtonX.pressing();
    Controller.ButtonY.pressing();
    Controller.ButtonA.pressing();
    Controller.ButtonB.pressing();
    Controller.ButtonUp.pressing();
    Controller.ButtonDown.pressing();
    Controller.ButtonRight.pressing();
    Controller.ButtonLeft.pressing();
    Controller.Axis1.value();
    Controller.Axis2.value();
    Controller.Axis3.value();
    Controller.Axis4.value();
  }
};
