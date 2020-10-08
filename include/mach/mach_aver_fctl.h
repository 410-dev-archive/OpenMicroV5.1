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
    // if (!Brain.SDcard.isInserted()) {
    //   cout << "not inserted" << endl;
    //   return false;
    // }
    try{
      ifstream fopen(loadFile.data());
      if (fopen.is_open()) {
        return true;
      }
      return false;
    }catch(exception e){
      return false;
    }
	}

	// Load string data from saved text file
	string loadString(string loadFile) {
		if (!Brain.SDcard.isInserted()) {
			return "";
		}else{
			ifstream openFile(loadFile.data());
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

	int saveString(string fileTitle, string contents) {
		if (!Brain.SDcard.isInserted()) {
			return 0;
		}else{
			ofstream writeFile (fileTitle, ofstream::out);
			if(writeFile.is_open()) {
				writeFile << contents + "\n";
				writeFile.close();
				return 1;
			}
			return -1;
		}
	}
};
