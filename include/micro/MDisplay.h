#include <string>

class MDisplay {
public: void init();
public: short setLinePrefix(int lineNumber, std::string text);
public: void setValueOfLine(short lineNumber, short prefixLength, std::string text);
public: void clearLine(int lineNumber);
public: void clearScreen();
};
