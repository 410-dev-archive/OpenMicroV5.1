/*

AVER Code Write Department

VEX V5 Sensor Utilities

*/

#include "vex.h"
#include <vex_triport.h>

using namespace vex;

class AESensorsUtility {
public:
  // Resets the encoder data to 0
  void resetShaftEncoderValue(encoder encoderObject) {
    encoderObject.resetRotation();
  }

  // Returns the data inside the specified encoder object value
	int getShaftEncoderValue(encoder encoderObject) {
    return encoderObject.value();
	}

  bool visionSensor(vision visionObject, int yuvData[], float rangeScaleFactor, int cameraData[]) {
    // Index order for yuvData
    // 0: ID
    // 1: u-axis minimum
    // 2: u-axis maximum
    // 3: u-axis average
    // 4: v-axis minimum
    // 5: v-axis maximum
    // 6: v-axis average
    // 7: signature type
    // 8: Brightness

    // Index order for cameraData (Originally named)
    // 0: mid_x
    // 1: cur_obj_cnt
    // 2: cur_obj_center_x


    vision::signature BLOB(yuvData[0], yuvData[1], yuvData[2], yuvData[3], yuvData[4], yuvData[5], yuvData[6], rangeScaleFactor, yuvData[7]);
    visionObject.setBrightness(yuvData[8]);

    // signature init
    visionObject.setSignature(BLOB);

    visionObject.takeSnapshot(BLOB);
    cameraData[1] = visionObject.objectCount;

    if(cameraData[1]){
      cameraData[2] = visionObject.largestObject.centerX;
      return true;
    }
    return false;
  }
};
