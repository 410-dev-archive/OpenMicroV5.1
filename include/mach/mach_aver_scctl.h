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
  void init() {
    Brain.Screen.render(true, false);
  }

  int setLinePrefix(int lineNumber, string text) {
    Brain.Screen.clearLine(lineNumber, color::black);
    Brain.Screen.setCursor(lineNumber, 0);
    const char *toPrint = text.c_str();
    Brain.Screen.print(toPrint);
    Brain.Screen.render();
    return text.length();
  }

  void setValueOfLine(int lineNumber, int prefixLength, string text) {
    Brain.Screen.clearLine(lineNumber, color::black);
    Brain.Screen.setCursor(lineNumber, prefixLength);
    const char *toPrint = text.c_str();
    Brain.Screen.print(toPrint);
    Brain.Screen.render();
  }

  void clearLine(int lineNumber) {
    Brain.Screen.clearLine(lineNumber, color::black);
    Brain.Screen.render();
  }

  void clearScreen() {
    Brain.Screen.clearScreen(color::black);
  }
};
