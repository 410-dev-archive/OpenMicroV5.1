/*

AVER Code Write Department

VEX V5 Macro Controller


*/

#include "vex.h"
#include <vector>
#include <string>

#include "hardwareinfo.h"

#include "mach/mach_aver_fctl.h"


using namespace vex;
using namespace std;

class AEMacroControl{
public:
	string loadedMacro_name = ""; // Holds macro identifier
	vector<string> loadedMacro_action{}; // Holds macro action in order
	vector<string> loadedMacro_time{}; // Holds macro time in order

	AEMacroControl(string argument) {
		
	}

	void loadMacro() {

	}


};