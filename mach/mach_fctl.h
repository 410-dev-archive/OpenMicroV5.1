#include "vex.h"
#include <string>

#include <fstream>
#include <iostream>

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
			return "";
		}else{
			ifstream openFile(fileName.data());
			if(openFile.is_open()) {
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
		if (!sdcard.isInserted()) {
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
}
