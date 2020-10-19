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

#include "mach/mach_main.h"

using namespace vex;
using namespace std;

competition Competition;
controller Controller;
RSManager System("");

// main
int main(){
  // Launches Resource Manager
  System.init();
  // vex::thread newTask(motorCall); // Motor Async Run

  System.status("Started motor!");
  System.mctl.runSingleMotor(PULL_MOTOR_1, directionType::fwd);
  System.mctl.runSingleMotor(PULL_MOTOR_2, directionType::fwd);
  System.status("Shaft encoder should work.");

  // Sets Encoder Value Prefix
  short lengthOfPrefix_LeftShaft = System.scctl.setLinePrefix(5, "Left Shaft Encoder Value: ");
  short lengthOfPrefix_RigthShaft = System.scctl.setLinePrefix(6, "Right Shaft Encoder Value: ");
  short lengthOfPrefix_BackShaft = System.scctl.setLinePrefix(7, "Back Shaft Encoder Value: ");
  short lengthOfPrefix_Vision = System.scctl.setLinePrefix(8, "Vision Sensor Value: ");
  System.status("Finished setting livedisplay prefix.");

  // Create vision sensor data
  /* 여기에서 빨간색 인식하게 코드좀 짜줘 */
  int yuvData[] = {0, 0, 10, 5, 0, 100, 50, 0, 50};
  int camData[] = {0, 0, 0};

  // Keep receives value from Shaft Encoder until motorctl.motorStatus is true.
  while(TERMINATION_SWITCH.value() == 0) {
    // Converts returned shaft encoder value to string and sets the value of line
    System.scctl.setValueOfLine(5, lengthOfPrefix_LeftShaft, System.convertToString(ENCODER_LEFT.value()));
    System.scctl.setValueOfLine(6, lengthOfPrefix_RigthShaft, System.convertToString(ENCODER_RIGHT.value()));
    System.scctl.setValueOfLine(7, lengthOfPrefix_BackShaft, System.convertToString(ENCODER_BACK.value()));
    System.scctl.setValueOfLine(8, lengthOfPrefix_Vision, System.convertToString(System.srutil.visionSensor(testVisionSensor, yuvData, 2.0, camData)));
  }

  System.status("Terminal switch pressed.");
  System.panic("System reached to end.", 0);

}
