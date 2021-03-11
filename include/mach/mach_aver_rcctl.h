#include "vex.h"
#include <string>
#include <sstream>
#include <vector>

#include "hardwareinfo.h"
#include "mach/BIOS/mach_aver_srutil.h"
#include "mach/BIOS/mach_aver_mtctl.h"

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
  vector<int> encSide = {0, 0};

  bool actionUpdate = false;
  bool liveControl = false;
  float multiplier = 1.0;

  string recentActivity = "";
  string FWD = "";
  string LFT = "";

  int condition = 0;
  float a, b, c, d, e, f;
  float speed = 25.0;

	void updateAll(controller Controller) {
    if (!liveControl) {
      encLeft.at(encLeft.size() - 1) = srutil.getShaftEncoderValue(ENCODER_LEFT);
      encRight.at(encRight.size() - 1) = srutil.getShaftEncoderValue(ENCODER_RIGHT);
      encSide.at(encSide.size() - 1) = srutil.getShaftEncoderValue(ENCODER_SIDE);
    }
    a=0;
    b=0;
    c=0;
    d=0;
    e=0;
    f=0;

    FWD = toString(Controller.Axis3.value());
    LFT = toString(Controller.Axis4.value());

    multiplier = 1.0;
    condition = 0;
    if (Controller.ButtonL1.pressing()){
      multiplier = 2.0;
    }
    if (Controller.ButtonL2.pressing()){
      multiplier = 4.0;
    }

    if (Controller.ButtonUp.pressing() || Controller.Axis3.value() > 60){
      e = 1;
      a = 100.0 * multiplier;
    }
    if (Controller.ButtonDown.pressing() || Controller.Axis3.value() < -60){
      e = 1;
      a = -100.0 * multiplier;
    }
    if (Controller.ButtonLeft.pressing() || Controller.Axis4.value() < -60 || Controller.Axis1.value() < -60){
      e = 1;
      b = 100 * multiplier;
    }
    if (Controller.ButtonRight.pressing() || Controller.Axis4.value() > 60 || Controller.Axis1.value() > 60){
      e = 1;
      b = -100 * multiplier;
    }
    if (Controller.ButtonA.pressing() || Controller.Axis2.value() > 60){
      e = 1;
      onPress_startPuller();
    }
    // else if (Controller.ButtonA.pressing() || Controller.Axis2.value() < -60){
    //   e = 1;
    //   onPress_startPuller2();
    // }
    if (0==e){
      onRelease_wheels();
      onRelease_puller();
    }
    else{
      onPress_bruuh(a, b);
    }
    //if (Controller.ButtonA.pressing()) onPress_systemTerminate();
  }

  void onPress_bruuh(int a, int b) {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "BRUH?";
    WHEEL_FRONT_LEFT.spin(directionType::fwd, (a-b)/2, velocityUnits::pct);
    WHEEL_FRONT_RIGHT.spin(directionType::fwd, (a+b)/2, velocityUnits::pct);
    WHEEL_BACK_LEFT.spin(directionType::fwd, (a-b)/2, velocityUnits::pct);
    WHEEL_BACK_RIGHT.spin(directionType::fwd, (a+b)/2, velocityUnits::pct);
  }

  void addIndex() {
    encLeft.push_back(0);
    encRight.push_back(0);
    encSide.push_back(0);
    srutil.resetShaftEncoderValue(ENCODER_LEFT);
    srutil.resetShaftEncoderValue(ENCODER_RIGHT);
    srutil.resetShaftEncoderValue(ENCODER_SIDE);
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
    mtctl.runMotors(allmotors, 4, directionType::rev, speed*multiplier);
  }

  void onPress_backward() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: BACKWARD";
    motor allmotors[] = {WHEEL_FRONT_LEFT,WHEEL_BACK_RIGHT,WHEEL_BACK_LEFT,WHEEL_FRONT_RIGHT};
    mtctl.runMotors(allmotors, 4, directionType::fwd, speed*multiplier);
  }

  void onPress_turnLeft() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: LEFT";
    motor toRunForward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
    motor toRunBackward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
    mtctl.runMotors(toRunForward, 2, directionType::fwd, speed*multiplier);
    mtctl.runMotors(toRunBackward, 2, directionType::rev, speed*multiplier);
  }

  void onPress_turnRight() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: RIGHT";
    motor toRunBackward[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
    motor toRunForward[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
    mtctl.runMotors(toRunForward, 2, directionType::fwd, speed*multiplier);
    mtctl.runMotors(toRunBackward, 2, directionType::rev, speed*multiplier);
  }

  void onPress_startPuller() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: PULL";
    motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2, INTAKE_LEFT, INTAKE_RIGHT};
    mtctl.runMotors(pullers, 4, directionType::fwd, speed*multiplier);
  }

  void onPress_startPuller2() {
    if(!actionUpdate) actionUpdate = true;
    recentActivity = "REMOTE: PULL";
    motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2, INTAKE_LEFT, INTAKE_RIGHT};
    mtctl.runMotors(pullers, 4, directionType::rev, speed*multiplier);
  }

  void onRelease_puller() {
    motor pullers[] = {PULL_MOTOR_1, PULL_MOTOR_2, INTAKE_LEFT, INTAKE_RIGHT};
    mtctl.stopMotors(pullers, 4);
  }



  void onPress_systemTerminate() {
    recentActivity = "REMOTE: STOP";
    mtctl.stopMotors(MOTOR_ALL, 8);
  }
};
