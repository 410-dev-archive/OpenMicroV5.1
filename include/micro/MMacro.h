#include "vex.h"
#include <vector>
#include <string>

class MMacro {
public: vector<int> leftEncoder;
public: vector<int> rightEncoder;
public: vector<int> sideEncoder;
// public: vector<int> getLeftEncoderVector();
// public: vector<int> getRightEncoderVector();
// public: vector<int> getSideEncoderVector();
public: void recordMacro(std::string fileName);
public: void loadMacro(std::string loadedMacro_name);
};