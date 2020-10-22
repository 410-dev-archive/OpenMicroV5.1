#include "vex.h"
// #include "mach/mach_aver_fctl.h"
#include "mach/mach_aver_scctl.h"
// #include "mach/mach_aver_srutil.h"
// #include "mach/mach_aver_mtctl.h"
#include "mach/mach_aver_rcctl.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace vex;
using namespace std;

class AESystem {
public:

  // RS Manager required value
  const short loggingLine = 4;
  vector<string> log{};

  // Able to access from other components
  // AEFileControl fctl;
  AEMotorControl mctl;
  // AESensorsUtility srutil;
  AEScreenControl scctl;
  AERemoteControl rcctl;

  // Constructor
  AESystem(string nd) {
    init();
  }

  // Shows basic logs
  void init(void) {
    scctl.init();
    scctl.clearScreen();
    scctl.setValueOfLine(1, 0, "Team AVER Mach - Test Version 0.0.4-3");
    scctl.setValueOfLine(2, 0, "=====================================");
  }

  // Set status
  void status(string logContent) {
    scctl.clearLine(loggingLine);
    log.push_back(logContent);
    scctl.setValueOfLine(loggingLine, 0, "Status: " + logContent);
  }

  void status(string logContent, int customLineNumber) {
    scctl.clearLine(customLineNumber);
    log.push_back(logContent);
    scctl.setValueOfLine(customLineNumber, 0, "Status: " + logContent);
  }

  // Provide panic and stops program
  void panic(string logContent, int exitCode){
    mctl.stopMotors(MOTOR_ALL, 8);
    scctl.clearScreen();
    scctl.setValueOfLine(1, 0, logContent);
    for(short i = 0; i < log.size(); i++) {
      scctl.setValueOfLine(i + 1, 0, log.at(i));
    }
    exit(exitCode);
  }

  /* 승모 여기서부터 작업하면 됨 */
  void livedisplay_configure() {}
  void livedisplay_updateValue() {}
  /* 여기까지 */

  // Convert int to string
  string convertToString(double data) {
    ostringstream oss;
    oss << data;
    return oss.str();
  }

};