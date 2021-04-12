/*

AVER Code Write Department

VEX V5 Brain File Controller

*/

#include "vex.h"
#include <string>

#include <fstream>
#include <iostream>

#include "micro/MFiles.h"

using namespace vex;
using namespace std;

// Checks whether a file exists or not
bool MFiles::doesFileExist(string loadFile) {
	if (!Brain.SDcard.isInserted()) {
	  return false;
	}
	ifstream fopen(loadFile.data());
	if (fopen.is_open()) {
		return true;
	}
	return false;
}

// Load string data from saved text file
string MFiles::loadString(string loadFile) {
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

int MFiles::saveString(string fileTitle, string contents) {
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