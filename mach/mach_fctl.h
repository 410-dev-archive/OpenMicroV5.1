#include "vex.h"
#include <vector>
#include <string>

using namespace vex;
using namespace std;

#define sdcard vex::brain::sdcard

class Filecontrol {
public:

	// Checks whether a file exists or not
	bool doesFileExists(string loadFile) {
		try{
			if (!sdcard.isInserted()) {
				return false;
			}

			char *fileName = new char[loadFile.length() + 1];
			strcpy(fileName, loadFile.c_str());

			int32_t fsize = sdcard::filesize(fileName);

			// Checks if the file size has value or not
			if (fsize != nullptr) {
				return true;
			}else{
				return false;
			}
		}catch(int exception){
			return false;
		}
	}

	// Load string data from saved text file
	string loadString(string fileName) {
		if (!sdcard.isInserted()) {
			return nullptr;  // Returns null if SD is not inserted
		}else{
			char *fileName = new char[saveFile.length() + 1];
			strcpy(fileName, saveFile.c_str());

			sdcard::loadtextfile()
		}
	}

	int saveString(string saveFile, string contents) {
		if (!sdcard.isInserted()) {
			return 0;
		}else{
			char *fileName = new char[saveFile.length() + 1];
			char *fileContent = new char[contents.length() + 1];
			strcpy(fileName, saveFile.c_str());
			strcpy(fileContent, contents.c_str());

			sdcard::savetextfile(fileName, fileContent);
		}
	}
}

class Printer {
public:
	int setLinePrefix(int lineNumber, string text) {
		// Set line prefix
		// Return length of prefix text
	}

	void setValueOfLine(int lineNumber, int prefixLength, string text) {
		// Set value
	}

	void clearLine(int lineNumber) {
		// Clear Line
	}
}