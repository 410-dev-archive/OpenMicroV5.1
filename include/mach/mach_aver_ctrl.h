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
  int buttonUp, buttonDown, buttonRight, buttonLeft;
  int ax1, ax2, ax3, ax4;
  int encLeft, encRight, encBack;

	void updateAll(controller Controller) {
    encLeft = aeutils.getShaftEncoderValue(ENCODER_LEFT);
    encRight = aeutils.getShaftEncoderValue(ENCODER_RIGHT);
    encBack = aeutils.getShaftEncoderValue(ENCODER_BACK);
    
    buttonR1 = Controller.ButtonR1.pressing();
    buttonR2 = Controller.ButtonR2.pressing();
    buttonL1 = Controller.ButtonL1.pressing();
    buttonL2 = Controller.ButtonL2.pressing();
    buttonX = Controller.ButtonX.pressing();
    buttonY = Controller.ButtonY.pressing();
    buttonA = Controller.ButtonA.pressing();
    buttonB = Controller.ButtonB.pressing();
    buttonUp = Controller.ButtonUp.pressing();
    buttonDown = Controller.ButtonDown.pressing();
    buttonRight = Controller.ButtonRight.pressing();
    buttonLeft = Controller.ButtonLeft.pressing();
    ax1 = Controller.Axis1.value();
    ax2 = Controller.Axis2.value();
    ax3 = Controller.Axis3.value();
    ax4 = Controller.Axis4.value();
  }
};
