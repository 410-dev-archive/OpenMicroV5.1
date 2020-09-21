#include "vex.h"
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace vex;
using namespace std;
competition Competition;


// motor variables
vex::controller Controller;
vex::motor LU (vex::PORT3, vex::gearSetting::ratio18_1, false);
vex::motor RU (vex::PORT4, vex::gearSetting::ratio18_1, true);
vex::motor LD (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor RD (vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::motor Intake1 (vex::PORT9, vex::gearSetting::ratio18_1, false);
vex::motor Intake2 (vex::PORT7, vex::gearSetting::ratio18_1, true);
vex::motor Arm (vex::PORT8, vex::gearSetting::ratio18_1, false);
vex::motor holdUp (vex::PORT5, vex::gearSetting::ratio18_1, false);

class RawInput{
  public:
    double frontback_value = 0;
    double rightleft_value = 0;
    double rot_value = 0;
    double arm_value = 0;
    double intake_value = 0;
    double holdup_value = 0;
    double division_value = 2;
};

class Velocity{
  public:
    double LU_velocity = 0;
    double RU_velocity = 0;
    double LD_velocity = 0;
    double RD_velocity = 0;
    double arm_velocity = 0;
    double intake_velocity = 0;
    double holdup_velocity = 0;

    void velocityCalc(RawInput x);
};

RawInput r;
Velocity v;

void Velocity::velocityCalc(RawInput x){
  LU_velocity = (x.frontback_value + x.rightleft_value + x.rot_value) / x.division_value;
  RU_velocity = (x.frontback_value - x.rightleft_value - x.rot_value) / x.division_value;
  LD_velocity = (x.frontback_value - x.rightleft_value + x.rot_value) / x.division_value;
  RD_velocity = (x.frontback_value + x.rightleft_value - x.rot_value) / x.division_value;
  arm_velocity = x.arm_value;
  intake_velocity = x.intake_value / x.division_value;
  holdup_velocity = x.holdup_value / x.division_value;

  if(Arm.rotation(rotationUnits::deg) > 360 * 3){
    arm_velocity = 0;
  }
}

vector<double> parse(string src, char delimeter){
  stringstream ss(src);
  string it;
  vector<double> sp;
  
  while(getline(ss, it, delimeter)){
    double td;
    stringstream temporary;
    temporary << it;
    temporary >> td;
    sp.push_back(td);
  }
  return sp;
}

void get_division(){
// Division Value Related Functions
  r.division_value = 2;
  if(Controller.ButtonR1.pressing()){
    r.division_value = 1;
  }
  if(Controller.ButtonR2.pressing()){
    r.division_value = 3;
  }
}

void get_holdup(){
  // Holdup Value Update
  r.holdup_value = 0;
  if(Controller.ButtonL1.pressing()){
    r.holdup_value = 100;
    r.arm_value = 100;
  }
  if(Controller.ButtonL2.pressing()){
    r.holdup_value = -100;
    r.arm_value = -100;
  }
}

void get_axis_motor(){
  // Get motor Value with Axis
  r.frontback_value = Controller.Axis3.value();
  r.rightleft_value = Controller.Axis4.value();
  r.rot_value = Controller.Axis1.value();

  r.arm_value = 0;
  if(Controller.ButtonY.pressing()){
    r.arm_value = 100;
  }
  if(Controller.ButtonA.pressing()){
    r.arm_value = -100;
  }

  r.intake_value = 0;
  if(Controller.ButtonX.pressing()){
    r.intake_value = 100;
  }
  if(Controller.ButtonB.pressing()){
    r.intake_value = -100;
  }
}

void get_button_motor(){
  // use the 4 controls for movement
  if(r.frontback_value == 0 && r.rightleft_value == 0){
    if(Controller.ButtonUp.pressing()){
      r.frontback_value = 100;
    }
    if(Controller.ButtonDown.pressing()){
      r.frontback_value = -100;
    }
    if(Controller.ButtonRight.pressing()){
      r.rightleft_value = 100;
    }
    if(Controller.ButtonLeft.pressing()){
      r.rightleft_value = -100;
    }
  }
}

void global_spin(Velocity inp){
  // move motor according to velocity
  LU.spin(directionType::fwd, inp.LU_velocity, velocityUnits::pct);
  RU.spin(directionType::fwd, inp.RU_velocity, velocityUnits::pct);
  LD.spin(directionType::fwd, inp.LD_velocity, velocityUnits::pct);
  RD.spin(directionType::fwd, inp.RD_velocity, velocityUnits::pct);
  Arm.spin(directionType::fwd, inp.arm_velocity, velocityUnits::pct);
  Intake1.spin(directionType::fwd, inp.intake_velocity, velocityUnits::pct);
  Intake2.spin(directionType::fwd, inp.intake_velocity, velocityUnits::pct);
  holdUp.spin(directionType::fwd, inp.holdup_velocity, velocityUnits::pct);
}

vector<double> v1, v2, v3, v4, v5, v6, v7;
// pre-auto code

void loader(void) {
  ifstream f1, f2, f3, f4, f5, f6, f7;
  string b1, b2, b3, b4, b5, b6, b7;
  f1.open("LU.txt"); f1 >> b1; f1.close();
  f2.open("RU.txt"); f2 >> b2; f2.close();
  f3.open("LD.txt"); f3 >> b3; f3.close();
  f4.open("RD.txt"); f4 >> b4; f4.close();
  f5.open("arm.txt"); f5 >> b5; f5.close();
  f6.open("intake.txt"); f6 >> b6; f6.close();
  f7.open("holdup.txt"); f7 >> b7; f7.close();

  v1 = parse(b1, '/');
  v2 = parse(b2, '/');
  v3 = parse(b3, '/');
  v4 = parse(b4, '/');
  v5 = parse(b5, '/');
  v6 = parse(b6, '/');
  v7 = parse(b7, '/');
}

void pre_auton(void) {
  vexcodeInit();
  // loader();
}  


void autonomous(void){
  for(int i=0; i<v1.size(); i++){
    double c1, c2, c3, c4, c5, c6, c7;
    Velocity cur_v;
    c1 = v1[i]; c2 = v2[i]; c3 = v3[i]; c4 = v4[i];
    c5 = v5[i]; c6 = v6[i]; c7 = v7[i];

    cur_v.LU_velocity = c1;
    cur_v.RU_velocity = c2;
    cur_v.LD_velocity = c3;
    cur_v.RD_velocity = c4;
    cur_v.arm_velocity = c5;
    cur_v.intake_velocity = c6;
    cur_v.holdup_velocity = c7;

    global_spin(cur_v);

  }
}

void usercontrol(void) {
  while (true) {
    get_division();
    get_holdup();
    get_axis_motor();
    get_button_motor();
    v.velocityCalc(r);
    global_spin(v);
  }
}

int main() {
  Arm.resetRotation();
  Arm.stop(brakeType::hold);
  pre_auton();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
}
