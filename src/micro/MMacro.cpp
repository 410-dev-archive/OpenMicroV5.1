/*

AVER Code Write Department

VEX V5 Macro Controller


*/

#include <stdlib.h>
#include "vex.h"
#include <vector>
#include <string>
#include <numeric>

#include "micro/hardlink.h"
#include "micro/MMacro.h"
#include "micro/MFiles.h"
#include "micro/MMotor.h"
#include "micro/MSensor.h"
#include "micro/MTypeConvert.h"

using namespace vex;
using namespace std;

vector<int> loadedMacro_left{};
vector<int> loadedMacro_right{};
vector<int> loadedMacro_side{};
vector<int> loadedMacro_totalTime{};

#ifndef files
#define files MFiles()
#endif
#ifndef motor
#define motor MMotor()
#endif
#ifndef sensor
#define sensor MSensor()
#endif
#ifndef typeConvert
#define typeConvert MTypeConvert()
#endif
#ifndef remote
#define remote MRemote()
#endif

void MMacro::recordMacro(string fileName) {
	string encoderLeft = typeConvert.stringJoin(remote.encLeft, " ");
	string encoderRight = typeConvert.stringJoin(remote.encRight, " ");
	string encoderSide = typeConvert.stringJoin(remote.encSide, " ");
	string totalTime = typeConvert.stringJoin(remote.times, " ");

	files.saveString(fileName + "_enc_Left", encoderLeft);
	files.saveString(fileName + "_enc_Right", encoderRight);
	files.saveString(fileName + "_enc_Side", encoderSide);
	files.saveString(fileName + "_total_Time", totalTime);
}

void MMacro::loadMacro(string loadedMacro_name) {
  string ttt;
  // ttt = fctl.loadString(loadedMacro_name + "_enc_Left");

  // while(1){
  //   debug_display.setValueOfLine(10, 0, "LOADED:"+ttt+":END");
  // }

	loadedMacro_left = typeConvert.stringSplitToInt(files.loadString(loadedMacro_name + "_enc_Left"), " ");
	loadedMacro_right = typeConvert.stringSplitToInt(files.loadString(loadedMacro_name + "_enc_Right"), " ");
	loadedMacro_side = typeConvert.stringSplitToInt(files.loadString(loadedMacro_name + "_enc_Side"), " ");
	loadedMacro_totalTime = typeConvert.stringSplitToInt(files.loadString(loadedMacro_name + "_total_Time"), " ");
	
	for(int i = 0; i < loadedMacro_left.size(); i++) {
		bool motorIsAlreadyRunning = false;
		short shouldStop = 0;
		
		while(loadedMacro_totalTime.at(i) > (Brain.timer(vex::timeUnits::msec) - remote.init_time)) {
			shouldStop = 0;
			if (!motorIsAlreadyRunning) {
				if (loadedMacro_left.at(i) > 0) motor.runMotors(MOTOR_WHEEL_LEFT, 2, vex::forward, 100);
				if (loadedMacro_left.at(i) < 0) motor.runMotors(MOTOR_WHEEL_LEFT, 2, vex::reverse, 100);
				if (loadedMacro_right.at(i) > 0) motor.runMotors(MOTOR_WHEEL_RIGHT, 2, vex::forward, 100);
				if (loadedMacro_right.at(i) < 0) motor.runMotors(MOTOR_WHEEL_RIGHT, 2, vex::reverse, 100);
				if (loadedMacro_side.at(i) != 0) motor.runMotors(MOTOR_PULL_BALL, 2, vex::forward, 100);
			}

			if (abs(loadedMacro_left.at(i) - sensor.getShaftEncoderValue(ENCODER_LEFT)) < 2) {
				motor.stopMotors(MOTOR_WHEEL_LEFT, 2);
				shouldStop++;
			}
			if (abs(loadedMacro_right.at(i) - sensor.getShaftEncoderValue(ENCODER_RIGHT)) < 2) {
				motor.stopMotors(MOTOR_WHEEL_RIGHT, 2); 
				shouldStop++;
			}
			if (abs(loadedMacro_side.at(i) - sensor.getShaftEncoderValue(ENCODER_SIDE)) < 2) {
				motor.stopMotors(MOTOR_PULL_BALL, 2);
				shouldStop++;
			}

		}
		
		
		// Before update - 2021 04 12
		// while(shouldStop < 3) {
		// 	shouldStop = 0;
		// 	if (!motorIsAlreadyRunning) {
		// 		if (loadedMacro_left.at(i) > 0) motor.runMotors(MOTOR_WHEEL_LEFT, 2, vex::forward, 100);
		// 		if (loadedMacro_left.at(i) < 0) motor.runMotors(MOTOR_WHEEL_LEFT, 2, vex::reverse, 100);
		// 		if (loadedMacro_right.at(i) > 0) motor.runMotors(MOTOR_WHEEL_RIGHT, 2, vex::forward, 100);
		// 		if (loadedMacro_right.at(i) < 0) motor.runMotors(MOTOR_WHEEL_RIGHT, 2, vex::reverse, 100);
		// 		if (loadedMacro_side.at(i) != 0) motor.runMotors(MOTOR_PULL_BALL, 2, vex::forward, 100);
		// 	}

		// 	if (abs(loadedMacro_left.at(i) - sensor.getShaftEncoderValue(ENCODER_LEFT)) < 2) {
		// 		motor.stopMotors(MOTOR_WHEEL_LEFT, 2);
		// 		shouldStop++;
		// 	}
		// 	if (abs(loadedMacro_right.at(i) - sensor.getShaftEncoderValue(ENCODER_RIGHT)) < 2) {
		// 		motor.stopMotors(MOTOR_WHEEL_RIGHT, 2); 
		// 		shouldStop++;
		// 	}
		// 	if (abs(loadedMacro_side.at(i) - sensor.getShaftEncoderValue(ENCODER_SIDE)) < 2) {
		// 		motor.stopMotors(MOTOR_PULL_BALL, 2);
		// 		shouldStop++;
		// 	}

		// }
	}
}
