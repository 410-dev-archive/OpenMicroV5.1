// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

#include "micro/MDisplay.h"
#include "micro/MRemote.h"
#include "micro/MFiles.h"
#include "micro/MMacro.h"
#include "micro/MTypeConvert.h"
#include "micro/hardlink.h"

using namespace vex;
using namespace std;

bool shouldImmediatelyExitLoop = false;

competition Competition;
controller Controller;

void global(string modeTitle) {
  // Shows title screen

  MDisplay display;
  MRemote remote;
  MTypeConvert convert;

  display.setValueOfLine(1, 0, "  Team AVER OpenMicroV5.1 Kernel - 1.0 Beta 1");
  display.setValueOfLine(2, 0, modeTitle + "===========================");


  // Sets Encoder Value Prefix
  short lengthOfPrefix_LeftShaft = display.setLinePrefix(3, "Left Shaft Encoder Value: ");
  short lengthOfPrefix_RigthShaft = display.setLinePrefix(4, "Right Shaft Encoder Value: ");
  short lengthOfPrefix_SideShaft = display.setLinePrefix(5, "Back Shaft Encoder Value: ");

  // Keep receives value from Shaft Encoder until motorctl.motorStatus is true.
  while(/*!Controller.ButtonA.pressing() && */!shouldImmediatelyExitLoop) {
    remote.updateAll(Controller);
    
    // Converts returned shaft encoder value to string and sets the value of line
    display.setValueOfLine(3, lengthOfPrefix_LeftShaft, convert.convertToString((int) ENCODER_RIGHT.value()));
    display.setValueOfLine(4, lengthOfPrefix_RigthShaft, convert.convertToString((int) ENCODER_RIGHT.value()));
    display.setValueOfLine(5, lengthOfPrefix_SideShaft, convert.convertToString((int) ENCODER_SIDE.value()));
    display.setValueOfLine(6, 0, remote.recentActivity + "           ");
    display.setValueOfLine(7, 0, "Forward / Backward: " + remote.FWD + "       ");
    display.setValueOfLine(8, 0, "Left / Right      : " + remote.LFT + "       ");
    // display.setValueOfLine(9, 0, "Encoder 1 Stored: " + convert.convertToString(remote.encLeft.size()) + ", " + convert.convertToString(remote.encLeft.at(remote.encLeft.size() - 2)));
    // display.setValueOfLine(10, 0, "Encoder 2 Stored: " + convert.convertToString(remote.encRight.size()) + ", " + convert.convertToString(remote.encRight.at(remote.encRight.size() - 2)));
    // display.setValueOfLine(11, 0, "Encoder 3 Stored: " + convert.convertToString(remote.encSide.size()) + ", " + convert.convertToString(remote.encSide.at(remote.encSide.size() - 2)));
  }
}

void remotemode() {
  MDisplay display;
  global("REMOTE CONTROL MODE");
  display.clearScreen();
  display.setValueOfLine(1, 0, "[*] Shutdown signal detected.");
  display.setValueOfLine(2, 0, "[*] Sensor update stopped...");
  display.setValueOfLine(3, 0, "[*] Main thread stopped...");
  display.setValueOfLine(4, 0, "[*] Goodbye.");
  exit(0);
}

void recordMacroSoftware(string fileName) {
  global("RECORD MACRO MODE");
  MDisplay display;
  MMacro macro;
  macro.recordMacro(fileName);
  display.clearScreen();
  display.setValueOfLine(1, 0, "[*] Record complete in file: " + fileName);
  display.setValueOfLine(2, 0, "[*] Software complete.");
  MRemote remote;
  remote.onPress_systemTerminate();
  exit(0);
}

void loadMacroSoftware(string fileName) {
  //global("MACRO LOAD AUTONOMOUS");
  MMacro macro;
  MDisplay display;
  macro.loadMacro(fileName);
  display.setValueOfLine(5, 0, "[*] End of load macro.");
  exit(0);
}

short menu() {
  MDisplay display;
  display.setValueOfLine(1, 0, "  Team AVER - MachMO System 2020 - 1.0 Beta 4");
  display.setValueOfLine(2, 0, " MAIN MENU:");
  display.setValueOfLine(3, 0, "X: Remote Control Only");
  display.setValueOfLine(4, 0, "Y: Record Macro");
  display.setValueOfLine(5, 0, "B: Load Macro");
  while(true) {
    if (Controller.ButtonX.pressing()) return 0;
    else if (Controller.ButtonY.pressing()) return 1;
    else if (Controller.ButtonB.pressing()) return 2;
  }
}

int main(){
  MDisplay display;
  MRemote remote;
  short output = menu();
  display.clearScreen();
  switch(output) {
    case 0:
      remote.liveControl = true;
      remotemode();

    case 1:
      remote.liveControl = false;
      recordMacroSoftware("DEMO");

    case 2:
      loadMacroSoftware("DEMO");

    default:
      exit(0);
  }
}