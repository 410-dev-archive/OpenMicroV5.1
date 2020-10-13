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

#include "RSManager/main.h"

using namespace vex;
using namespace std;

competition Competition;
vex::controller Controller;
RSManager System;

// Method for async (vex::thread)
void motorCall() {
  motor motorArray[] = {TEST};
  System.mctl.runMotor(motorArray, 1, 5000);
}

// main
int main(){
  // Launches Resource Manager
  System.init();

  vex::thread newTask(motorCall); // Motor Async Run

  // Sets Encoder Value Prefix
  short lengthOfPrefix_ShaftEncoder = System.scctl.setLinePrefix(5, "Shaft Encoder Value: ");

  // Keep receives value from Shaft Encoder until motorctl.motorStatus is true.
  while(System.mctl.isMotorSessionRunning()) {
    // Converts returned shaft encoder value to string and sets the value of line
    stringstream sstream;
    sstream << (System.srutil.getShaftEncoderValue(EncoderA), "");
    System.scctl.setValueOfLine(5, lengthOfPrefix_ShaftEncoder, sstream.str());
  }
}