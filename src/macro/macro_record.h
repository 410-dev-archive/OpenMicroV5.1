/*

macro_record.h

Team AVER [Advanced Vex EngineeRs]

2020.Sept.15

This header contains function that records macro.

Iteration Build: 1

*/

vector<int> macro_action_storage;
/* Action Code:

	1: Go Forward
	2: Go Backward

	11: Rotate Left
	12: Rotate Right

	21: Pickup Ball
	22: Output Ball

*/
vector<int> macro_motorpower_storage;
vector<float> macro_time_storage;

bool didMacroSaved = false;

int macro_record_start() { // Start recording macro
	if (didMacroSaved) {
		// Overwriting macro.
		// User need to press designated key map to actually rewrite
	}else{
		// Start recording macro
	}
}
