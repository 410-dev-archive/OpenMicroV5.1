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

//#define sdcard vex::brain::sdcard

class AEFileControl {
public:
	// Checks whether a file exists or not
	bool doesFileExists(string loadFile) {
		if (!Brain.SDcard.isInserted()) {
		  cout << "[AEFileControl] SDCard is not recognised.\n";
		  return false;
		}

		cout << "[AEFileControl] Checking file exists: " + loadFile + "\n";
		try{
			ifstream fopen(loadFile.data());
			if (fopen.is_open()) {
				cout << "[AEFileControl] fopen is open. (File exists)\n";
				return true;
			}
			cout << "[AEFileControl] fopen is closed. (File not exists)\n";
			return false;
		}catch(exception e){
			cout << "[AEFileControl] Encountered error. (Probably file not exists)\n";
			return false;
		}
	}

	// Load string data from saved text file
	string loadString(string loadFile) {
		cout << "[AEFileControl] Loading file: " + loadFile + "\n";
		if (!Brain.SDcard.isInserted()) {
			cout << "[AEFileControl] SDCard does is not recognised. Empty data should be returned.\n";
			return "";
		}else{
			cout << "[AEFileControl] SDCard recognised, reading with ifstream.\n";
			ifstream openFile(loadFile.data());
			if(openFile.is_open()) {
				cout << "[AEFileControl] Found file.\n";
       			string line;
				string constructReturn = "";
				while(getline(openFile, line)) {
					constructReturn += line + "\n";
					cout << "[AEFileControl] Read line: " + line + "\n";
				}
				cout << "[AEFileControl] Final data = " + constructReturn + "\n";
				return constructReturn;
			}
			cout << "[AEFileControl] openFile is close, probably file does not exists.\n";
			return "";
		}
	}

	int saveString(string fileTitle, string contents) {
		cout << "[AEFileControl] Saving data \"" + contents + "\" with title \"" + fileTitle + "\"\n";
		if (!Brain.SDcard.isInserted()) {
			cout << "[AEFileControl] SDCard is not recognised.\n";
			return 0;
		}else{
			ofstream writeFile (fileTitle, ofstream::out);
			if(writeFile.is_open()) {
				writeFile << contents + "\n";
				writeFile.close();
				cout << "[AEFileControl] Writing complete.\n";
				return 1;
			}
			cout << "[AEFileControl] writeFile is closed. This is an error.\n";
			return -1;
		}
	}
};
