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
vex::motor Intake1 (vex::PORT6, vex::gearSetting::ratio18_1, false);
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

void Velocity::velocityCalc(RawInput x){
  LU_velocity = (x.frontback_value + x.rightleft_value + x.rot_value) / x.division_value;
  RU_velocity = (x.frontback_value - x.rightleft_value - x.rot_value) / x.division_value;
  LD_velocity = (x.frontback_value - x.rightleft_value + x.rot_value) / x.division_value;
  RD_velocity = (x.frontback_value + x.rightleft_value - x.rot_value) / x.division_value;
  arm_velocity = x.arm_value / x.division_value;
  intake_velocity = x.intake_value / x.division_value;
  holdup_velocity = x.holdup_value / x.division_value;
}


RawInput r;
Velocity v;

string to_string(double val){
  stringstream k;
  k << val;
  return k.str();
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
  }
  if(Controller.ButtonL2.pressing()){
    r.holdup_value = -100;
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

// pre-auto code
void pre_auton(void) {
  vexcodeInit();
}

void autonomous(void){
  
}



// recording : 1 / finished : 0
int recording = -1;

vector<double> LU_velocities;
vector<double> RU_velocities;
vector<double> LD_velocities;
vector<double> RD_velocities;
vector<double> arm_velocities;
vector<double> intake_velocities;
vector<double> holdup_velocities;

void usercontrol(void) {
  while (true) {
    if(Controller.ButtonR1.pressing() && Controller.ButtonR2.pressing()){
      recording = 1;
    }
    if(Controller.ButtonL1.pressing() && Controller.ButtonL2.pressing()){
      recording = 0;
    }
    get_division();
    get_holdup();
    get_axis_motor();
    get_button_motor();

    v.velocityCalc(r);
    global_spin(v);

    if(recording == 1){
      // v_save.push_back(v);
      LU_velocities.push_back(v.LU_velocity);
      RU_velocities.push_back(v.RU_velocity);
      LD_velocities.push_back(v.LD_velocity);
      RD_velocities.push_back(v.RD_velocity);
      arm_velocities.push_back(v.arm_velocity);
      intake_velocities.push_back(v.intake_velocity);
      holdup_velocities.push_back(v.holdup_velocity);
    }
    if(recording == 0){
      string b1="", b2="", b3="", b4="", b5="", b6="", b7="";
      for(auto x1: LU_velocities) b1 += to_string(x1)+'/';
      for(auto x2: RU_velocities) b2 += to_string(x2)+'/';
      for(auto x3: LD_velocities) b3 += to_string(x3)+'/';
      for(auto x4: RD_velocities) b4 += to_string(x4)+'/';
      for(auto x5: arm_velocities) b5 += to_string(x5)+'/';
      for(auto x6: intake_velocities) b6 += to_string(x6)+'/';
      for(auto x7: holdup_velocities) b7 += to_string(x7)+'/';
      b1.pop_back(); b2.pop_back(); b3.pop_back(); b4.pop_back();
      b5.pop_back(); b6.pop_back(); b7.pop_back();

      ofstream f1, f2, f3, f4, f5, f6, f7;
      f1.open("LU.txt"); f1 << b1; f1.close();
      f2.open("RU.txt"); f2 << b2; f2.close();
      f3.open("LD.txt"); f3 << b3; f3.close();
      f4.open("RD.txt"); f4 << b4; f4.close();
      f5.open("arm.txt"); f5 << b5; f5.close();
      f6.open("intake.txt"); f6 << b6; f6.close();
      f7.open("holdup.txt"); f7 << b7; f7.close();
      break;
    }
  }
}

int main() {
  pre_auton();

  Arm.stop(brakeType::hold);
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
}
