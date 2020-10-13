#include "vex.h"
#include "mach/mach_aver_fctl.h"
#include "mach/mach_aver_scctl.h"
#include "mach/mach_aver_srutil.h"
#include "mach/mach_aver_mtctl.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace vex;
using namespace std;

class RSManager {
private:
  string runArgument = "";

  void startScreen() {
    scctl.init();
    scctl.clearScreen();
    scctl.setValueOfLine(1, 0, "Team AVER Mach - Test Version 0.0.1");
    scctl.setValueOfLine(2, 0, "===================================");
  }

public:
  AEFileControl fctl;
  AEMotorControl mctl;
  AESensorsUtility srutil;
  AEScreenControl scctl;

  RSManager(string startupArgument) {
    runArgument = startupArgument;
    init();
  }

  RSManager() {
    init();
  }

  void init(void) {
    startScreen();
    scctl.setValueOfLine(3, 0, "Program Argument: " + runArgument);
    scctl.setValueOfLine(4, 0, "RSManager should accept request from main binary.");
  }
};