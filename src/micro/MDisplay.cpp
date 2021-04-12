#include "vex.h"
#include <string>
#include "micro/MDisplay.h"



// Initializes screen
void MDisplay::init() {
  Brain.Screen.render(true, false);
}

// Should be used as labeling data
short MDisplay::setLinePrefix(int lineNumber, std::string text) {
  Brain.Screen.clearLine(lineNumber, color::black);
  Brain.Screen.setCursor(lineNumber, 0);
  const char *toPrint = text.c_str();
  Brain.Screen.print(toPrint);
  Brain.Screen.render();
  return (short) text.length();
}

// Set value of line, could be use as setting the entire line or after the data label
void MDisplay::setValueOfLine(short lineNumber, short prefixLength, std::string text) {
  Brain.Screen.setCursor(lineNumber, prefixLength);
  const char *toPrint = text.c_str();
  Brain.Screen.print(toPrint);
  Brain.Screen.render();
}

// Clears specified line
void MDisplay::clearLine(int lineNumber) {
  Brain.Screen.clearLine(lineNumber, color::black);
  Brain.Screen.render();
}

// Clears entire screen
void MDisplay::clearScreen() {
  Brain.Screen.clearScreen(color::black);
}
