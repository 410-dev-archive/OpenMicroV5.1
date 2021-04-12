// /*----------------------------------------------------------------------------*/
// /*                                                                            */
// /*    Module:       main.cpp                                                  */
// /*    Author:       eric-1                                                    */
// /*    Created:      Thu Sep 24 2020                                           */
// /*    Description:  V5 project                                                */
// /*                                                                            */
// /*----------------------------------------------------------------------------*/

// // ---- START VEXCODE CONFIGURED DEVICES ----
// // ---- END VEXCODE CONFIGURED DEVICES ----

// #include "vex.h"
// #include "hardwareinfo.h"
// #include "mach/mach_aver_fctl.h"
// #include "mach/mach_aver_scctl.h"
// #include "mach/mach_aver_srutil.h"
// #include "mach/mach_aver_mtctl.h"
// #include <iostream>

// using namespace vex;
// using namespace std;

// competition Competition;
// vex::controller Controller;

// // pre-autonomous code
// void pre_auton(void){
//   vexcodeInit();
// }

// // autonomous code
// void autonomous(void){

// }

// //user control
// void usercontrol(void){
//   AEFileControl averFileController;
//   bool r = averFileController.doesFileExists("test.txt");
//   cout<<r<<endl;
//   while (true){
//     wait(20, msec);
//   }
// }

// // main
// int main(){
//   // Sensor Test - Displayed on Brain
//   AEScreenControl scctl;
//   scctl.

//   short lengthOfPrefix_ShaftEncoder = scctl.setLinePrefix(1, "Shaft Encoder Value: ");


//   // Motor should run
//   AEMotorControl motorctl;
//   motor motorArray[] = {TEST};
//   motorctl.runMotor(motorArray, 1, 5000);


// }