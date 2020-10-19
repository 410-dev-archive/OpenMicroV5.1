#include "vex.h"

using namespace vex;

// Motors
// vex::motor LeftBack (vex::PORT3, vex::gearSetting::ratio18_1, false);
// vex::motor RightFront (vex::PORT4, vex::gearSetting::ratio18_1, true);
// vex::motor LeftFront (vex::PORT1, vex::gearSetting::ratio18_1, false);
// vex::motor RightBack (vex::PORT2, vex::gearSetting::ratio18_1, true);
// vex::motor Intake1 (vex::PORT9, vex::gearSetting::ratio18_1, false);
// vex::motor Intake2 (vex::PORT7, vex::gearSetting::ratio18_1, true);
// vex::motor Arm (vex::PORT8, vex::gearSetting::ratio18_1, false);
// vex::motor holdUp (vex::PORT5, vex::gearSetting::ratio18_1, false);
motor PULL_MOTOR_1 (vex::PORT1, vex::gearSetting::ratio18_1, true); // Param: (Port, GearSetting, Reverse);
motor PULL_MOTOR_2 (vex::PORT2, vex::gearSetting::ratio18_1, false);

motor WHEEL_FRONT_LEFT (vex::PORT3, vex::gearSetting::ratio18_1, false);
motor WHEEL_BACK_LEFT (vex::PORT4, vex::gearSetting::ratio18_1, false);
motor WHEEL_FRONT_RIGHT (vex::PORT5, vex::gearSetting::ratio18_1, true);
motor WHEEL_BACK_RIGHT (vex::PORT6, vex::gearSetting::ratio18_1, true);

motor DUMMY(vex::PORT7, vex::gearSetting::ratio18_1, false);
motor DUMMY2(vex::PORT8, vex::gearSetting::ratio18_1, false);

motor MOTOR_PULL_BALL[] = {PULL_MOTOR_1, PULL_MOTOR_2};

// Sensors
triport threeWirePort(PORT22);
encoder ENCODER_LEFT = encoder(threeWirePort.A);
encoder ENCODER_RIGHT = encoder(threeWirePort.C);
encoder ENCODER_BACK = encoder(threeWirePort.E);

limit TERMINATION_SWITCH = limit(threeWirePort.G);

vision testVisionSensor = vision(12); // Vision Sensor (port)