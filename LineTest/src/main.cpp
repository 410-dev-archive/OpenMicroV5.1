#include "vex.h"
#include <iostream>

vex::motor m1(vex::PORT4, vex::gearSetting::ratio18_1, false);

using namespace vex;
using namespace std;

class Printer {
public:
  void printline(int line_num, char *line_str){
    Brain.Screen.clearLine(line_num, color::black);
    Brain.Screen.setCursor(line_num, 0);
    Brain.Screen.print(line_str);
  }
};

Printer p_mod;
string cur_message;

int main(void){
  Brain.Screen.render(true, false);
  m1.setVelocity(10, velocityUnits::pct);
  while(true){
    sprintf(cur_message, "AHHHHHHHHHHHH %d", rand());
    m1.spin(directionType::fwd);
    p_mod.printline(1, );
    Brain.Screen.render();
  }
}