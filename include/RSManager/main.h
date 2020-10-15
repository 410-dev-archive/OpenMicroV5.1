#include "vex.h"
#include "mach/mach_aver_fctl.h"
#include "mach/mach_aver_scctl.h"
#include "mach/mach_aver_srutil.h"
#include "mach/mach_aver_mtctl.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace vex;
using namespace std;

class RSManager {
public:

  // RS Manager required value
  string runArgument = "";
  const short loggingLine = 4;
  vector<string> log{};

  // Able to access from other components
  AEFileControl fctl;
  AEMotorControl mctl;
  AESensorsUtility srutil;
  AEScreenControl scctl;

  // Constructor with startup argument
  RSManager(string startupArgument) {
    runArgument = startupArgument; // Set arg in private storage
    init();
  }

  // Constructor without startup argument
  RSManager() {
    init();
  }

  // Shows basic logs
  void init(void) {
    scctl.init();
    scctl.clearScreen();
    scctl.setValueOfLine(1, 0, "Team AVER Mach - Test Version 0.0.4-3");
    scctl.setValueOfLine(2, 0, "=====================================");
    scctl.setValueOfLine(3, 0, "Program Argument: " + runArgument);
  }

  // Set status
  void status(string logContent) {
    scctl.clearLine(loggingLine);
    if (!runArgument.find("--no-log")) log.push_back(logContent);
    scctl.setValueOfLine(loggingLine, 0, "Status: " + logContent);
  }

  // Provide panic and stops program
  void panic(string logContent, int exitCode){
    scctl.clearScreen();
    scctl.setValueOfLine(1, 0, logContent);
    for(short i = 0; i < log.size(); i++) {
      scctl.setValueOfLine(i + 3, 0, log.at(i));
    }
    exit(exitCode);
  }

  // Convert int to string
  string convertToString(double data) {
    ostringstream oss;
    oss << data;
    return oss.str();
  }
};