/*

AVER Code Write Department

VEX V5 Macro Controller


*/

#include "vex.h"
#include <vector>
#include <string>
#include <numeric>

using namespace vex;
using namespace std;

class AEMacroControl{
public:
	string loadedMacro_action_name = ""; // Holds macro identifier
	string loadedMacro_time_name = ""; // Holds macro identifier
	vector<int> loadedMacro_left{};
	vector<int> loadedMacro_right{};
	vector<int> loadedMacro_side{};

	void recordMacro(AERemoteControl rcctl, string fileName, AEFileControl fctl) {
		string encoderLeft = join(rcctl.encLeft);
		string encoderRight = join(rcctl.encRight);
		string encoderSide = join(rcctl.encSide);

		fctl.saveString(fileName + "_enc_Left", encoderLeft);
		fctl.saveString(fileName + "_enc_Right", encoderRight);
		fctl.saveString(fileName + "_enc_Side", encoderSide);
	}

	string join(vector<int> vect) {
		string str = "";
		
		for(short i = 0; i < vect.size(); i++) str += convertToString(vect.at(i)) + "," ;
		return str;
	}


	string convertToString(int data) {
		std::ostringstream strstream;
		strstream << data;
		return strstream.str();
	}

	void loadMacro(AEScreenControl scctl, AEFileControl fctl, string loadedMacro_name) {
		loadedMacro_left = parseFileVector(fctl.loadString(loadedMacro_name + "_enc_Left"), " ", scctl);
		// loadedMacro_right = parseFileVector(fctl.loadString(loadedMacro_name + "_enc_Right"), " ");
		// loadedMacro_side = parseFileVector(fctl.loadString(loadedMacro_name + "_enc_Side"), " ");

		int index = 0;

		// DEBUG
		int sum = accumulate(loadedMacro_left.begin(), loadedMacro_left.end(), 0);
		scctl.setValueOfLine(3, 0, "DATA: " + convertToString(sum));
		// END DEBUG

	}

	int returnAsInteger(string s) {
		return atoi(s.c_str());
	}

 	vector<int> parseFileVector(string s, string separator, AEScreenControl scctl) {
		size_t positionStart = 0, positionEnd = 0, separatorLength = separator.length();
		string tkn;
		vector<int> returnData;

		stringstream ss(s);
		for(int i; ss >> i;) {
			returnData.push_back(i);
			if (ss.peek() == ',') ss.ignore();
		}
		return returnData;
  	}
};