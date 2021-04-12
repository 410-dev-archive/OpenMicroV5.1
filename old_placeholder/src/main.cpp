// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"


#include "mach/BIOS/mach_aver_scctl.h"
#include "mach/mach_aver_rcctl.h"
#include "mach/BIOS/mach_aver_fctl.h"
#include "mach/mach_aver_macro.h"

using namespace vex;
using namespace std;

bool shouldImmediatelyExitLoop = false;

competition Competition;
controller Controller;

AEScreenControl scctl;
AERemoteControl rcctl;
AEMacroControl mcctl;
AEFileControl fctl;

string toString(int data) {
  std::ostringstream strstream;
  strstream << data;
  return strstream.str();
}

void global(string modeTitle) {
  // Shows title screen
  scctl.setValueOfLine(1, 0, "  Team AVER - MachMO System 2020 - 1.0 Beta 4");
  scctl.setValueOfLine(2, 0, modeTitle + "===========================");


  // Sets Encoder Value Prefix
  short lengthOfPrefix_LeftShaft = scctl.setLinePrefix(3, "Left Shaft Encoder Value: ");
  short lengthOfPrefix_RigthShaft = scctl.setLinePrefix(4, "Right Shaft Encoder Value: ");
  short lengthOfPrefix_SideShaft = scctl.setLinePrefix(5, "Back Shaft Encoder Value: ");

  // Keep receives value from Shaft Encoder until motorctl.motorStatus is true.
  while(/*!Controller.ButtonA.pressing() && */!shouldImmediatelyExitLoop) {
    shouldImmediatelyExitLoop = rcctl.updateAll(Controller);
    
    // Converts returned shaft encoder value to string and sets the value of line
    scctl.setValueOfLine(3, lengthOfPrefix_LeftShaft, toString(ENCODER_LEFT.value()));
    scctl.setValueOfLine(4, lengthOfPrefix_RigthShaft, toString(ENCODER_RIGHT.value()));
    scctl.setValueOfLine(5, lengthOfPrefix_SideShaft, toString(ENCODER_SIDE.value()));
    scctl.setValueOfLine(6, 0, rcctl.recentActivity + "           ");
    scctl.setValueOfLine(7, 0, "Forward / Backward: " + rcctl.FWD + "       ");
    scctl.setValueOfLine(8, 0, "Left / Right      : " + rcctl.LFT + "       ");
    scctl.setValueOfLine(9, 0, "Encoder 1 Stored: " + toString(rcctl.encLeft.size()) + ", " + toString(rcctl.encLeft.at(rcctl.encLeft.size() - 2)));
    scctl.setValueOfLine(10, 0, "Encoder 2 Stored: " + toString(rcctl.encRight.size()) + ", " + toString(rcctl.encRight.at(rcctl.encRight.size() - 2)));
    scctl.setValueOfLine(11, 0, "Encoder 3 Stored: " + toString(rcctl.encSide.size()) + ", " + toString(rcctl.encSide.at(rcctl.encSide.size() - 2)));
  }
}

void remotemode() {
  global("REMOTE CONTROL MODE");
  scctl.clearScreen();
  scctl.setValueOfLine(1, 0, "[*] Shutdown signal detected.");
  scctl.setValueOfLine(2, 0, "[*] Sensor update stopped...");
  scctl.setValueOfLine(3, 0, "[*] Main thread stopped...");
  scctl.setValueOfLine(4, 0, "[*] Goodbye.");
  exit(0);
}

void recordMacroSoftware(string fileName) {
  global("RECORD MACRO MODE");
  mcctl.recordMacro(rcctl, fileName, fctl);
  scctl.clearScreen();
  scctl.setValueOfLine(1, 0, "[*] Record complete in file: " + fileName);
  scctl.setValueOfLine(2, 0, "[*] Software complete.");
  rcctl.onPress_systemTerminate();
  exit(0);
}

void loadMacroSoftware(string fileName) {
  //global("MACRO LOAD AUTONOMOUS");
  mcctl.loadMacro(scctl, fctl, fileName);
  scctl.setValueOfLine(5, 0, "[*] End of load macro.");
  exit(0);
}

short menu() {
  scctl.setValueOfLine(1, 0, "  Team AVER - MachMO System 2020 - 1.0 Beta 4");
  scctl.setValueOfLine(2, 0, " MAIN MENU:");
  scctl.setValueOfLine(3, 0, "X: Remote Control Only");
  scctl.setValueOfLine(4, 0, "Y: Record Macro");
  scctl.setValueOfLine(5, 0, "B: Load Macro");
  while(true) {
    if (Controller.ButtonX.pressing()) return 0;
    else if (Controller.ButtonY.pressing()) return 1;
    else if (Controller.ButtonB.pressing()) return 2;
  }
}

int main(){
  short output = menu();
  scctl.clearScreen();
  switch(output) {
    case 0:
      rcctl.liveControl = true;
      remotemode();

    case 1:
      rcctl.liveControl = false;
      recordMacroSoftware("DEMO");

    case 2:
      loadMacroSoftware("DEMO");

    default:
      exit(0);
  }
}