/*

AVER Code Write Department

VEX V5 Sensor Utilities

*/

#include "vex.h"
#include <vex_triport.h>

#include "micro/MSensor.h"

using namespace vex;

// Resets the encoder data to 0
void MSensor::resetShaftEncoderValue(encoder encoderObject) {
  encoderObject.resetRotation();
}

// Returns the data inside the specified encoder object value
int MSensor::getShaftEncoderValue(encoder encoderObject) {
  return encoderObject.value();
}

