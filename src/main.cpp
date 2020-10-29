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


#include "mach/B_IO/mach_aver_scctl.h"
#include "mach/mach_aver_rcctl.h"
#include "mach/B_IO/mach_aver_fctl.h"

using namespace vex;
using namespace std;

competition Competition;
controller Controller;

// This is program argument that will used across the system.
// The usable arguments are:
// --livecontrol      Macro cannot be recorded. Remote controller will not store encoder value. The performance may be enhanced.
// --no-output        Output does not show. This only applies to AEScreenControl, therefore manual print will still work.

string arg = ""; 

AEScreenControl scctl(arg);
AERemoteControl rcctl(arg);

// main

string toString(int data) {
  std::ostringstream strstream;
  strstream << data;
  return strstream.str();
}

void minimalStart() {
  string text = "Program Argument: " + arg;
  Brain.Screen.clearLine(1, color::black);
  Brain.Screen.setCursor(1, 0);
  const char *toPrint = text.c_str();
  Brain.Screen.print(toPrint);
  Brain.Screen.render();
}

void realSoftware() {
  // minimalStart();
  // Shows title screen
  scctl.setValueOfLine(1, 0, "  Team AVER - MachMO System 2020 - 1.0 Beta 3");
  scctl.setValueOfLine(2, 0, "===============================================");


  // Sets Encoder Value Prefix
  short lengthOfPrefix_LeftShaft = scctl.setLinePrefix(3, "Left Shaft Encoder Value: ");
  short lengthOfPrefix_RigthShaft = scctl.setLinePrefix(4, "Right Shaft Encoder Value: ");
  short lengthOfPrefix_BackShaft = scctl.setLinePrefix(5, "Back Shaft Encoder Value: ");

  // Keep receives value from Shaft Encoder until motorctl.motorStatus is true.
  while(TERMINATION_SWITCH.value() == 0 && !Controller.ButtonA.pressing()) {
    rcctl.updateAll(Controller);
    
    // Converts returned shaft encoder value to string and sets the value of line
    scctl.setValueOfLine(3, lengthOfPrefix_LeftShaft, toString(ENCODER_LEFT.value()));
    scctl.setValueOfLine(4, lengthOfPrefix_RigthShaft, toString(ENCODER_RIGHT.value()));
    scctl.setValueOfLine(5, lengthOfPrefix_BackShaft, toString(ENCODER_BACK.value()));
    scctl.setValueOfLine(6, 0, rcctl.recentActivity + "           ");
    scctl.setValueOfLine(7, 0, "Forward / Backward: " + rcctl.FWD + "       ");
    scctl.setValueOfLine(8, 0, "Left / Right      : " + rcctl.LFT + "       ");
    scctl.setValueOfLine(9, 0, "Encoder 1 Stored: " + toString(rcctl.encLeft.size()) + ", " + toString(rcctl.encLeft.at(rcctl.encLeft.size() - 2)));
    scctl.setValueOfLine(10, 0, "Encoder 2 Stored: " + toString(rcctl.encRight.size()) + ", " + toString(rcctl.encRight.at(rcctl.encRight.size() - 2)));
    scctl.setValueOfLine(11, 0, "Encoder 3 Stored: " + toString(rcctl.encBack.size()) + ", " + toString(rcctl.encBack.at(rcctl.encBack.size() - 2)));
  }
  
  scctl.clearScreen();
  scctl.setValueOfLine(1, 0, "[*] Shutdown signal detected.");
  scctl.setValueOfLine(2, 0, "[*] Sensor update stopped...");
  scctl.setValueOfLine(3, 0, "[*] Main thread stopped...");
  scctl.setValueOfLine(4, 0, "[*] Goodbye.");
  exit(0);
}

int main(){
  realSoftware();
  
}