#include "vex.h"
#include <string>

class MFiles {
public: bool doesFileExist(std::string loadFile);
public: std::string loadString(std::string loadFile);
public: int saveString(std::string fileTitle, std::string contents);
};
