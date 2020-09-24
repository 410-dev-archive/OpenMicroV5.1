/*

AVER Code Write Department

VEX V5 Brain File Controller

*/

#include "vex.h"
#include <string>

#include <fstream>
#include <iostream>

using namespace vex;
using namespace std;

#define sdcard vex::brain::sdcard

class AEFileControl {
public:
	// Checks whether a file exists or not
	bool doesFileExists(string loadFile) {
    if (!Brain.SDcard.isInserted()) {
      cout << "not inserted" << endl;
      return false;
    }

    char *fileName = new char[loadFile.length() + 1];
    strcpy(fileName, loadFile.c_str());
    return true;

    /*
    int32_t fsize = Brain.SDcard.filesize(fileName);

    // Checks if the file size has value or not
    if (fsize != nullptr) {
      return true;
    }else{
      return false;
    }
    */
	}

	// Load string data from saved text file
	string loadString(string fileName) {
		if (!Brain.SDcard.isInserted()) {
			return "";
		}else{
			ifstream openFile(fileName.data());
			if(openFile.is_open()) {
        string line;
				string constructReturn = "";
				while(getline(openFile, line)) {
					constructReturn += line + "\n";
				}
				return constructReturn;
			}
			return "";
		}
	}

	int saveString(string saveFile, string contents) {
		if (!Brain.SDcard.isInserted()) {
			return 0;
		}else{
			ofstream writeFile(saveFile.data());
			if(writeFile.is_open()) {
				writeFile << contents + "\n";
				writeFile.close();
				return 1;
			}
			return -1;
		}
	}
};
