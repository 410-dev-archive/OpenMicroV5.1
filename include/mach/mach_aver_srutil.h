/*

AVER Code Write Department

VEX V5 Sensor Utilities

*/

#include "vex.h"
#include <vex_triport.h>

using namespace vex;

class AESensorsUtility {
public:
	int getShaftEncoderValue() {
		return 0;
	}
};


// vision sensor test code for later

int id = 1;           // signature id
int uMin = 101;       // min u-axis
int uMax = 3217;      // max u-axis
int uMean = 1659;     // mean u-axis
int vMin = -4681;     // min v-axis
int vMax = -3869;     // max v-axis
int vMean = -4275;    // mean v-axis
float range = 2.3;    // range scale factor
int type = 0;         // signature type


vex::vision vs(vex::PORT9);
vex::vision::signature BLOB(id, uMin, uMax, uMean, vMin, vMax, vMean, range, type);

int main(void) {
  // brightness init
  vs.setBrightness(50);

  // signature init
  vs.setSignature(BLOB);

  // camera width: 316 pixel
  int mid_x = 316 / 2;
  int cur_obj_cnt = 0;
  int cur_obj_center_x = 0;

  while(true){

    // snapshot taken
    vs.takeSnapshot(BLOB);

    cur_obj_cnt = vs.objectCount;

    if(cur_obj_cnt){
      cur_obj_center_x = vs.largestObject.centerX;
    }
  }
}