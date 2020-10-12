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

// pre-autonomous code
void pre_auton(void){
  vexcodeInit();
}

// autonomous code
void autonomous(void){

}

//user control
void usercontrol(void){
  AEFileControl averFileController;
  bool r = averFileController.doesFileExists("test.txt");
  cout<<r<<endl;
  while (true){
    wait(20, msec);
  }
void motorCall() {
  motor motorArray[] = {TEST};
  motorctl.runMotor(motorArray, 1, 5000);
}

// main
int main(){
  usercontrol();
  // Sensor Test - Displayed on Brain
  AEScreenControl scctl;
  scctl.init();
  scctl.clearScreen();
  scctl.setValueOfLine(1, 0, "Team AVER Mach Core - Test Version 0.0.1");
  scctl.setValueOfLine(2, 0, "========================================");
  scctl.setValueOfLine(3, 0, "Code should run now.");

  short lengthOfPrefix_ShaftEncoder = scctl.setLinePrefix(4, "Shaft Encoder Value: ");

  vex::thread newTask(motorCall); // Motor Async Run
  AESensorsUtility sensorutil;

  while(motorctl.isMotorSessionRunning()) {
    stringstream sstream;
    // sstream << "Hello World";
    sstream << (sensorutil.getShaftEncoderValue(EncoderA), "");
    scctl.setValueOfLine(4, lengthOfPrefix_ShaftEncoder, sstream.str());
  }
}