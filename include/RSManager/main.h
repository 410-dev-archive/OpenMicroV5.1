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

  // Live Display related content
  const short livedisplay_maximum_line = 5;
  const short linePrefixOffset = 5;
  vector<short> livedisplay_allocatedLineNumber{};
  vector<short> livedisplay_allocatedLine_prefixLength{};
  vector<string> livedisplay_allocatedLine_label{};

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
    scctl.setValueOfLine(1, 0, "Team AVER Mach - Test Version 0.0.1");
    scctl.setValueOfLine(2, 0, "===================================");
    scctl.setValueOfLine(3, 0, "Program Argument: " + runArgument);
  }

  // Set status
  void status(string logContent) {
    scctl.clearLine(loggingLine);
    log.push_back(logContent);
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

  // Configure live display, with prefix. Should call once for one sensor data
  void setLiveDisplay(string label, string content) {
    short index = 0; // Set index to 0 (Linear search)
    while(livedisplay_allocatedLine_label.at(index) != label && index < livedisplay_maximum_line) index++; // Loop until matching element exists 
    if (index + 1 < livedisplay_maximum_line) return; // If exists, then method quits
    livedisplay_allocatedLineNumber.push_back(livedisplay_allocatedLine_label.size() + linePrefixOffset); // Sets line number
    livedisplay_allocatedLine_prefixLength.push_back(scctl.setLinePrefix(index + linePrefixOffset, content)); // Sets prefix offset
    livedisplay_allocatedLine_label.push_back(label); // Store label
  }

  // Update live display value after prefix
  void updateLiveDisplay(string label, string content) {
    short index = 0; // Sets index to 0 (Linear search)
    while(livedisplay_allocatedLine_label.at(index) == label && index <= livedisplay_maximum_line) index++; // Searches label if exists
    if (index + 1 == livedisplay_maximum_line) return; // If does not exists then quit
    scctl.setValueOfLine(livedisplay_allocatedLineNumber.at(index), livedisplay_allocatedLine_prefixLength.at(index), " " + content); // Update using scctl
  }

  // Convert int to string
  string convertToString(double data) {
    stringstream sstream;
    sstream << (data, "");
    return sstream.str();
  }
};