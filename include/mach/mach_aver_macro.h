/*

AVER Code Write Department

VEX V5 Macro Controller


*/

#include <stdlib.h>
#include "vex.h"
#include <vector>
#include <string>
#include <numeric>

using namespace vex;
using namespace std;

class AEMacroControl{
public:
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
		loadedMacro_left = parseFileVector(fctl.loadString(loadedMacro_name + "_enc_Left"), " ");
		loadedMacro_right = parseFileVector(fctl.loadString(loadedMacro_name + "_enc_Right"), " ");
		loadedMacro_side = parseFileVector(fctl.loadString(loadedMacro_name + "_enc_Side"), " ");

		AESensorsUtility senutil;
		AEMotorControl motctl;
		
		for (int i = 0; i < loadedMacro_left.size(); i++) {
			bool motorIsAlreadyRunning = false;
			short shouldStop = 0;
			while(shouldStop < 3) {
				shouldStop = 0;
				if (!motorIsAlreadyRunning) {
					if (loadedMacro_left.at(i) > 0) motctl.runMotors(MOTOR_WHEEL_LEFT, 2, vex::forward, 100);
					if (loadedMacro_left.at(i) < 0) motctl.runMotors(MOTOR_WHEEL_LEFT, 2, vex::reverse, 100);
					if (loadedMacro_right.at(i) > 0) motctl.runMotors(MOTOR_WHEEL_RIGHT, 2, vex::forward, 100);
					if (loadedMacro_right.at(i) < 0) motctl.runMotors(MOTOR_WHEEL_RIGHT, 2, vex::reverse, 100);
					if (loadedMacro_side.at(i) != 0) motctl.runMotors(MOTOR_PULL_BALL, 2, vex::forward, 100);
				}

				if (abs(loadedMacro_left.at(i) - senutil.getShaftEncoderValue(ENCODER_LEFT)) < 2) {
					motctl.stopMotors(MOTOR_WHEEL_LEFT, 2);
					shouldStop++;
				}
				if (abs(loadedMacro_right.at(i) - senutil.getShaftEncoderValue(ENCODER_RIGHT)) < 2) {
					motctl.stopMotors(MOTOR_WHEEL_RIGHT, 2); 
					shouldStop++;
				}
				if (abs(loadedMacro_side.at(i) - senutil.getShaftEncoderValue(ENCODER_SIDE)) < 2) {
					motctl.stopMotors(MOTOR_PULL_BALL, 2);
					shouldStop++;
				}

			}
		}
	}

	int returnAsInteger(string s) {
		return atoi(s.c_str());
	}

 	vector<int> parseFileVector(string s, string separator) {
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