/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       eric-1                                                    */
/*    Created:      Thu Sep 24 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "hardwareinfo.h"
#include "mach/mach_aver_fctl.h"
#include "mach/mach_aver_scctl.h"
#include "mach/mach_aver_srutil.h"
#include "mach/mach_aver_mtctl.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace vex;
using namespace std;

competition Competition;
vex::controller Controller;
AEMotorControl motorctl;

// Method for async (vex::thread)
void motorCall() {
  motor motorArray[] = {TEST};
  motorctl.runMotor(motorArray, 1, 5000);
}

// main
int main(){
  // Sensor Test - Displayed on Brain
  AEScreenControl scctl;
  scctl.init();
  scctl.clearScreen();
  scctl.setValueOfLine(1, 0, "Team AVER Mach - Test Version 0.0.1");
  scctl.setValueOfLine(2, 0, "===================================");
  scctl.setValueOfLine(3, 0, "[LOG] Code should run now.");
  scctl.setValueOfLine(4, 0, "[LOG] Starting mach_aver_motor in async thread.");
  vex::thread newTask(motorCall); // Motor Async Run

  // Create Object  
  AESensorsUtility sensorutil;

  // Sets Encoder Value Prefix
  short lengthOfPrefix_ShaftEncoder = scctl.setLinePrefix(5, "Shaft Encoder Value: ");

  // Keep receives value from Shaft Encoder until motorctl.motorStatus is true.
  while(motorctl.isMotorSessionRunning()) {
    // Converts returned shaft encoder value to string and sets the value of line
    stringstream sstream;
    sstream << (sensorutil.getShaftEncoderValue(EncoderA), "");
    scctl.setValueOfLine(5, lengthOfPrefix_ShaftEncoder, sstream.str());
  }
}