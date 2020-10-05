/*

AVER Code Write Department

VEX V5 Macro Controller

Depends on:
	mach_aver_fctl purely written by AVER team
	mach_aver_sctl purely written by AVER team
	mach_aver_rcctl purely written by AVER team

*/

#include "vex.h"
#include <vector>
#include <string>

#include "hardwareinfo.h"

#include "mach/mach_aver_fctl.h"
#include "mach/mach_aver_sctl.h"
#include "mach/mach_aver_rcctl.h"

using namespace vex;
using namespace std;

class AEMacroControl{
private:
	string loadedMacro_name = ""; // Holds macro identifier
	vector<string> loadedMacro_action{}; // Holds macro action in order
	vector<string> loadedMacro_time{}; // Holds macro time in order

	const string fileWithMacroList = "macro_file_table";
	AEScreencontrol screen;
public:

	// Load macro by file name
	// Takes macro file name, returns loaded status (0 = OK, 1 = Not OK)
	int loadMacro(string macroName) {

		// Write on screen
		screen.clearScreen();
		screen.setLinePrefix(1, "[MACRO_LOAD] Loading Macro: " + macroName);

		// Load file
		AEFileControl averFileController;
		string time = averFileController.loadString(macroName + "_time"); // Loads: examplemacro_time
		string actions = averFileController.loadString(macroName + "_action"); // Loads: examplemacro_action

		// Reset memory
		loadedMacro_name = "";
		loadedMacro_action.clear();
		loadedMacro_time.clear();

		// Transfer loaded file to memory
		loadedMacro_name = macroName;
		/* Split actions with "," and assign to loadedMacro_action */
		/* Split time with "," and assign to loadedMacro_time */

		// Returns exit status
		if (!loadedMacro_time.empty() && !loadedMacro_action.empty()) {
			screen.setLinePrefix(2, "[MACRO_LOAD] Macro Loaded: " + macroName);
			return 0;
		}else{
			screen.setLinePrefix(2, "[MACRO_LOAD] Error while loading macro: " + macroName);
			screen.setLinePrefix(3, "[MACRO_LOAD] One or more macro vectors are empty.");
			return 1;
		}
	}

	// Select saved macro via remote control
	// Takes no arg, returns selected macro file name
	string macroSelect() {

		// Load master file table
		AEFileControl averFileController;
		string contents = averFileController.loadString(fileWithMacroList);

		// Use remote control to select macro
		string selectedMacroName = "";

		/* (Undefined yet; Please complete rcctl.h first)
		while ( // Confirm button pressed ) {
			// Read button click

			// Print to screen
		}
		*/

		return selectedMacroName;
	}


	void runMacro() {
		// Don't code here yet
	}
};