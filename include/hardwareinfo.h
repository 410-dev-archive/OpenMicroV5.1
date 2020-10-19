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



motor WHEEL_FBMOVEMENT[] = {};
motor WHEEL_ROTATE_LEFTSET[] = {};
motor WHEEL_ROTATE_RIGHTSET[] = {};
motor MOTOR_PULL_BALL[] = {PULL_MOTOR_1, PULL_MOTOR_2};

// Sensors
triport threeWirePort(PORT22);
encoder testShaftEncoder = encoder(threeWirePort.A);
vision testVisionSensor = vision(2);encoder ENCODER_LEFT = encoder(threeWirePort.A);
encoder ENCODER_RIGHT = encoder(threeWirePort.C);
encoder ENCODER_BACK = encoder(threeWirePort.E);

limit TERMINATION_SWITCH = limit(threeWirePort.G);

vision testVisionSensor = vision(12); // Vision Sensor (port)