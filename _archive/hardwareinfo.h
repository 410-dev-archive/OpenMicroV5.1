#include "vex.h"

vex::controller Controller;

// Motors
vex::motor LU (vex::PORT3, vex::gearSetting::ratio18_1, false);
vex::motor RU (vex::PORT4, vex::gearSetting::ratio18_1, true);
vex::motor LD (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor RD (vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::motor Intake1 (vex::PORT9, vex::gearSetting::ratio18_1, false);
vex::motor Intake2 (vex::PORT7, vex::gearSetting::ratio18_1, true);
vex::motor Arm (vex::PORT8, vex::gearSetting::ratio18_1, false);
vex::motor holdUp (vex::PORT5, vex::gearSetting::ratio18_1, false);

// Sensors
