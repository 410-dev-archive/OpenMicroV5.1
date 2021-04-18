#include "vex.h"
#include "micro/hardlink.h"

using namespace vex;

// Motors

motor INTAKE_LEFT (vex::PORT5, vex::gearSetting::ratio18_1, true); // Param: (Port, GearSetting, Reverse);
motor INTAKE_RIGHT (vex::PORT6, vex::gearSetting::ratio18_1, false);

motor WHEEL_FRONT_LEFT (vex::PORT3, vex::gearSetting::ratio18_1, true);
motor WHEEL_BACK_LEFT (vex::PORT4, vex::gearSetting::ratio18_1, false);
motor WHEEL_FRONT_RIGHT (vex::PORT1, vex::gearSetting::ratio18_1, false);
motor WHEEL_BACK_RIGHT (vex::PORT2, vex::gearSetting::ratio18_1, true);

motor BALLCONVEY_UPPER(vex::PORT7, vex::gearSetting::ratio18_1, false);
motor BALLCONVEY_LOWER(vex::PORT8, vex::gearSetting::ratio18_1, false);

motor MOTOR_PULL_BALL[] = {INTAKE_LEFT, INTAKE_RIGHT};
motor MOTOR_ALL[] = {INTAKE_LEFT, INTAKE_RIGHT, WHEEL_BACK_LEFT, WHEEL_BACK_RIGHT, WHEEL_FRONT_LEFT, WHEEL_FRONT_RIGHT, BALLCONVEY_LOWER, BALLCONVEY_UPPER};

motor MOTOR_WHEELS_ALL[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT, WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
motor MOTOR_PULLER_ALL[] = {INTAKE_LEFT, INTAKE_RIGHT, BALLCONVEY_LOWER, BALLCONVEY_UPPER};

motor MOTOR_WHEEL_LEFT[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
motor MOTOR_WHEEL_RIGHT[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};

// Sensors
triport threeWirePort(PORT22);
encoder ENCODER_LEFT = encoder(threeWirePort.A);
encoder ENCODER_RIGHT = encoder(threeWirePort.C);
encoder ENCODER_SIDE = encoder(threeWirePort.E);
