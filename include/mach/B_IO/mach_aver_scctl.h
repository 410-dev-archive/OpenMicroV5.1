/*

AVER Code Write Department

VEX V5 Brain Screen Controller

*/

#include "vex.h"
#include <string>

using namespace vex;
using namespace std;

class AEScreenControl {
public:
  bool showOutput = true;

  // Initializes screen
  void init() {
    Brain.Screen.render(true, false);
  }

  // Should be used as labeling data
  short setLinePrefix(int lineNumber, string text) {
    if (showOutput) {
      Brain.Screen.clearLine(lineNumber, color::black);
      Brain.Screen.setCursor(lineNumber, 0);
      const char *toPrint = text.c_str();
      Brain.Screen.print(toPrint);
      Brain.Screen.render();
      return (short) text.length();
    }else{
      return 0;
    }
  }

  // Set value of line, could be use as setting the entire line or after the data label
  void setValueOfLine(short lineNumber, short prefixLength, string text) {
    if (showOutput) {
      Brain.Screen.setCursor(lineNumber, prefixLength);
      const char *toPrint = text.c_str();
      Brain.Screen.print(toPrint);
      Brain.Screen.render();
    }
  }

  // Clears specified line
  void clearLine(int lineNumber) {
    Brain.Screen.clearLine(lineNumber, color::black);
    Brain.Screen.render();
  }

  // Clears entire screen
  void clearScreen() {
    Brain.Screen.clearScreen(color::black);
  }
};
