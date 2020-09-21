#include "vex.h"
#include <string>

using namespace vex;
using namespace std;

class Printer {
public:
  void init() {
    Brain.Screen.render(true, false);
  }

  int setLinePrefix(int lineNumber, string text) {
    Brain.Screen.clearLine(lineNumber, color::black);
    Brain.Screen.setCursor(lineNumber, 0);
    Brain.Screen.print(text);
    Brain.Screen.render();
    return text.length();
  }

  void setValueOfLine(int lineNumber, int prefixLength, string text) {
    Brain.Screen.clearLine(lineNumber, color::black);
    Brain.Screen.setCursor(lineNumber, prefixLength);
    Brain.Screen.print(text);
    Brain.Screen.render();
  }

  void clearLine(int lineNumber) {
    Brain.Screen.clearLine(lineNumber, color::black);
    Brain.Screen.render();
  }
};
