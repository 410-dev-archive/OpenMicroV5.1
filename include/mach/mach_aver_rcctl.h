#include "vex.h"
#include <string>
#include <sstream>
#include <vector>

#include "hardwareinfo.h"
#include "mach/B_IO/mach_aver_srutil.h"
#include "mach/B_IO/mach_aver_mtctl.h"

using namespace vex;
using namespace std;

class AERemoteControl {
private:
  AEMotorControl mtctl;
  AESensorsUtility srutil;

  string toString(int data) {
    std::ostringstream strstream;
    strstream << data;
    return strstream.str();
  }


public:
  // vector<int> masterTimeline = {0}; // 1 = left, 2 = right, 3 = back
  vector<int> encLeft = {0, 0};
  vector<int> encRight = {0, 0};
  vector<int> encBack = {0, 0};

  bool actionUpdate = false;
  bool liveControl = false;

  string recentActivity = "";
  string FWD = "";
  string LFT = "";

  float speed = 1;

  AERemoteControl(string arg) {
    if (arg.find("--livecontrol") < 100000) liveControl = true;
  }

	void updateAll(controller Controller) {
    if (!liveControl) {
      encLeft.at(encLeft.size() - 1) = srutil.getShaftEncoderValue(ENCODER_LEFT);
      encRight.at(encRight.size() - 1) = srutil.getShaftEncoderValue(ENCODER_RIGHT);
      encBack.at(encBack.size() - 1) = srutil.getShaftEncoderValue(ENCODER_BACK);
    }

    FWD = toString(Controller.Axis3.value());
    LFT = toString(Controller.Axis4.value());

    if (Controller.ButtonUp.pressing() || Controller.Axis3.value() > 120) onPress_forward();
    else if (Controller.ButtonDown.pressing() || Controller.Axis3.value() < -120) onPress_backward();
    else if (Controller.ButtonLeft.pressing() || Controller.Axis4.value() < -120) onPress_turnLeft();
    else if (Controller.ButtonRight.pressing() || Controller.Axis4.value() > 120) onPress_turnRight();
    else if (Controller.ButtonX.pressing() || Controller.Axis2.value() > 120) onPress_startPuller();
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
    actionUpdate = false;
  }

  void onRelease_wheels() {
    if(actionUpdate && !liveControl) addIndex();
    recentActivity = "REMOTE: RELEASED";
    motor allmotors[] = {WHEEL_FRONT_LEFT,WHEEL_BACK_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT};
    mtctl.stopMotors(allmotors, 4);
  }

  void onPress_forward() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: FORWARD";
    motor allmotors[] = {WHEEL_FRONT_LEFT,WHEEL_BACK_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT};
    mtctl.runMotors(allmotors, 4, directionType::fwd, speed);
  }

  void onPress_backward() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: BACKWARD";
    motor allmotors[] = {WHEEL_FRONT_LEFT,WHEEL_BACK_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT};
    mtctl.runMotors(allmotors, 4, directionType::rev, speed);
  }

  void onPress_turnLeft() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: LEFT";
    motor toRunForward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
    motor toRunBackward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
    mtctl.runMotors(toRunForward, 2, directionType::fwd, 1);
    mtctl.runMotors(toRunBackward, 2, directionType::rev, 1);
  }

  void onPress_turnRight() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: RIGHT";
    motor toRunBackward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
    motor toRunForward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
    mtctl.runMotors(toRunForward, 2, directionType::fwd, 1);
    mtctl.runMotors(toRunBackward, 2, directionType::rev, 1);
  }

  void onPress_startPuller() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: PULL";
    motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2};
    mtctl.runMotors(pullers, 2, directionType::fwd, 1);
  }

  void onRelease_puller() {
    motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2};
    mtctl.stopMotors(pullers, 2);
  }

  void onPress_systemTerminate() {
    recentActivity = "REMOTE: STOP";
    mtctl.stopMotors(MOTOR_ALL, 8);
  }
};
