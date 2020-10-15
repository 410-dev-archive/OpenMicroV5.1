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
#include <future>

#include "hardwareinfo.h"

#include "RSManager/main.h"

using namespace vex;
using namespace std;

competition Competition;
controller Controller;
RSManager System("");

void async_task() {
  System.status("Started async function.");
  task::sleep(1000);
  System.status("Motor stop!");
  System.mctl.stopSingleMotor(TEST);
}

// main
int main(){
  // Launches Resource Manager
  System.init();
  // vex::thread newTask(motorCall); // Motor Async Run

  System.status("Started motor!");
  System.mctl.runSingleMotor(TEST);
  System.status("Shaft encoder should work.");

  // Sets Encoder Value Prefix
  short lengthOfPrefix_ShaftEncoder = System.scctl.setLinePrefix(5, "Shaft Encoder Value: ");
  short lengthOfPrefix_VisionSensor = System.scctl.setLinePrefix(6, "Vision Sensor Value: ");
  System.status("Finished setting livedisplay prefix..");

  // Create vision sensor data
  /* 여기에서 빨간색 인식하게 코드좀 짜줘 */
  int yuvData[] = {0, 0, 10, 5, 0, 100, 50, 0, 50};
  int camData[] = {0, 0, 0};

  // Keep receives value from Shaft Encoder until motorctl.motorStatus is true.
  while(System.mctl.motorStatus) {
    // Converts returned shaft encoder value to string and sets the value of line
    System.scctl.setValueOfLine(5, lengthOfPrefix_ShaftEncoder, System.convertToString(testShaftEncoder.value()));
    System.scctl.setValueOfLine(6, lengthOfPrefix_VisionSensor, System.convertToString(System.srutil.visionSensor(testVisionSensor, yuvData, 2.0, camData)));
  }
}
