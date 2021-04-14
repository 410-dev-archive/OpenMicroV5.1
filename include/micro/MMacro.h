#include "vex.h"
#include <vector>
#include <string>
#include "micro/MRemote.h"
#include "micro/MDisplay.h"

class MMacro {
public: vector<int> leftEncoder;
public: vector<int> rightEncoder;
public: vector<int> sideEncoder;
// public: vector<int> getLeftEncoderVector();
// public: vector<int> getRightEncoderVector();
// public: vector<int> getSideEncoderVector();
public: void recordMacro(MRemote remote, std::string fileName, MDisplay debug_display);
public: void loadMacro(std::string loadedMacro_name, MDisplay debug_display);
};