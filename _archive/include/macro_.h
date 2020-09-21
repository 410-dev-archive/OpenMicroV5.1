/*

macro_.h

Team AVER [Advanced Vex EngineeRs]

2020.Sept.15

This header includes macro headers in order.

Iteration Build: 1

*/

#include <vector>

std::vector<int> macro_action_storage;
/* Action Code:

	1: Go Forward
	2: Go Backward

	11: Rotate Left
	12: Rotate Right

	21: Pickup Ball
	22: Output Ball

*/
std::vector<int> macro_motorpower_storage;
std::vector<float> macro_time_storage;

bool didMacroSaved = false;

class Macro{
public:
  int macro_record_start() { // Start recording macro
    if (didMacroSaved) {
      // Overwriting macro.
      // User need to press designated key map to actually rewrite
      return 0;
    }else{
      // Start recording macro
      return 0;
    }
  }

  int macro_load() {
    return 0;
  }
};