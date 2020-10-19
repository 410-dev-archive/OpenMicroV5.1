/*

AVER Code Write Department

VEX V5 Brain Remote Controller

*/

#include "vex.h"
#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include "hardwareinfo.h"
#include "mach/mach_aver_srutil.h"
#include "mach/mach_aver_mtctl.h"
#include "mach/mach_main.h"

using namespace vex;
using namespace std;

#define WHEEL_ALL {WHEEL_FRONT_LEFT,WHEEL_FRONT_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT}

class AERemoteControl {
public:
  AEMotorControl mtctl;
  AESystem System;
  AESensorsUtility srutil;
  // bool buttonR1, buttonR2, buttonL1, buttonL2;
  // bool buttonX, buttonY, buttonA, buttonB;
  // bool buttonUp, buttonDown, buttonRight, buttonLeft;
  // int32_t ax1, ax2, ax3, ax4;

  vector<int> encLeft = {0};
  vector<int> encRight = {0};
  vector<int> encBack = {0};

	void updateAll(controller Controller) {
    encLeft.at(encLeft.size() - 1) = srutil.getShaftEncoderValue(ENCODER_LEFT);
    encRight.at(encRight.size() - 1) = srutil.getShaftEncoderValue(ENCODER_RIGHT);
    encBack.at(encBack.size() - 1) = srutil.getShaftEncoderValue(ENCODER_BACK);
    
    // buttonR1 = Controller.ButtonR1.pressing();
    // buttonR2 = Controller.ButtonR2.pressing();
    // buttonL1 = Controller.ButtonL1.pressing();
    // buttonL2 = Controller.ButtonL2.pressing();
    // buttonX = Controller.ButtonX.pressing();
    // buttonY = Controller.ButtonY.pressing();
    // buttonA = Controller.ButtonA.pressing();
    // buttonB = Controller.ButtonB.pressing();
    // buttonUp = Controller.ButtonUp.pressing();
    // buttonDown = Controller.ButtonDown.pressing();
    // buttonRight = Controller.ButtonRight.pressing();
    // buttonLeft = Controller.ButtonLeft.pressing();
    // ax1 = Controller.Axis1.value();
    // ax2 = Controller.Axis2.value();
    // ax3 = Controller.Axis3.value();
    // ax4 = Controller.Axis4.value();

    if (Controller.ButtonUp.pressing()) onPress_forward();
    else if (Controller.ButtonDown.pressing()) onPress_backward();
    else if (Controller.ButtonLeft.pressing()) onPress_turnLeft();
    else if (Controller.ButtonRight.pressing()) onPress_turnRight();
    else if (Controller.ButtonX.pressing()) onPress_startPuller();
    else{
      onRelease_wheels();
      onRelease_puller();
    }

    if (Controller.ButtonA.pressing()) onPress_systemTerminate();
  }

  void addIndex() {
    encLeft.push_back(0);
    encRight.push_back(0);
    encBack.push_back(0);
    srutil.resetShaftEncoderValue(ENCODER_LEFT);
    srutil.resetShaftEncoderValue(ENCODER_RIGHT);
    srutil.resetShaftEncoderValue(ENCODER_BACK);
  }

  void onRelease_wheels() {
    motor allmotors[] = WHEEL_ALL;
    mtctl.stopMotors(allmotors, 4);
  }

  void onPress_forward() {

    motor allmotors[] = WHEEL_ALL;
    mtctl.runMotors(allmotors, 4, directionType::fwd);
  }

  void onPress_backward() {
    motor allmotors[] = WHEEL_ALL;
    mtctl.runMotors(allmotors, 4, directionType::rev);
  }

  void onPress_turnLeft() {
    motor toRunForward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
    motor toRunBackward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
    mtctl.runMotors(toRunForward, 2, directionType::fwd);
    mtctl.runMotors(toRunBackward, 2, directionType::rev);
  }

  void onPress_turnRight() {
    motor toRunBackward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
    motor toRunForward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
    mtctl.runMotors(toRunForward, 2, directionType::fwd);
    mtctl.runMotors(toRunBackward, 2, directionType::rev);
  }

  void onPress_startPuller() {
    motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2};
    mtctl.runMotors(pullers, 2, directionType::fwd);
  }

  void onRelease_puller() {
    motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2};
    mtctl.stopMotors(pullers, 2);
  }

  void onPress_systemTerminate() {
    System.panic("System terminated.", 0);
  }
};
