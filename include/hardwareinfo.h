#include "vex.h"

using namespace vex;

// Motors
motor PULL_MOTOR_1 (vex::PORT1, vex::gearSetting::ratio18_1, false); // Param: (Port, GearSetting, Reverse);
motor PULL_MOTOR_2 (vex::PORT2, vex::gearSetting::ratio18_1, false);

motor WHEEL_FRONT_LEFT (vex::PORT3, vex::gearSetting::ratio18_1, true);
motor WHEEL_BACK_LEFT (vex::PORT4, vex::gearSetting::ratio18_1, false);
motor WHEEL_FRONT_RIGHT (vex::PORT5, vex::gearSetting::ratio18_1, false);
motor WHEEL_BACK_RIGHT (vex::PORT6, vex::gearSetting::ratio18_1, true);

motor INTAKE_RIGHT(vex::PORT7, vex::gearSetting::ratio18_1, true);
motor INTAKE_LEFT(vex::PORT8, vex::gearSetting::ratio18_1, false);

motor MOTOR_PULL_BALL[] = {PULL_MOTOR_1, PULL_MOTOR_2};
motor MOTOR_ALL[] = {PULL_MOTOR_1, PULL_MOTOR_2, WHEEL_BACK_LEFT, WHEEL_BACK_RIGHT, WHEEL_FRONT_LEFT, WHEEL_FRONT_RIGHT, INTAKE_LEFT, INTAKE_RIGHT};

//motor MOTOR_INTAKE[] = {INTAKE_LEFT, INTAKE_RIGHT};

motor MOTOR_WHEELS_ALL[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT, WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};
// motor MOTOR_PULLER_ALL[] = {PULL_MOTOR_1, PULL_MOTOR_2};
motor MOTOR_PULLER_ALL[] = {PULL_MOTOR_1, PULL_MOTOR_2, INTAKE_LEFT, INTAKE_RIGHT};

motor MOTOR_WHEEL_LEFT[] = {WHEEL_FRONT_LEFT, WHEEL_BACK_LEFT};
motor MOTOR_WHEEL_RIGHT[] = {WHEEL_FRONT_RIGHT, WHEEL_BACK_RIGHT};

// Sensors
triport threeWirePort(PORT22);
encoder ENCODER_LEFT = encoder(threeWirePort.A);
encoder ENCODER_RIGHT = encoder(threeWirePort.C);
encoder ENCODER_SIDE = encoder(threeWirePort.E);

vision testVisionSensor = vision(12); // Vision Sensor (port)