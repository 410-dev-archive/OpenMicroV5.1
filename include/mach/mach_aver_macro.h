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

  vector<string> splitStr(string s, string del) {
    size_t p_st = 0, p_end, delim_len = del.length();
    string tkn;
    vector<string> tkns;

    while((p_end = s.find(del, p_st)) != string::npos) {
      tkn = s.substr(p_st, p_end - p_st);
      p_st = p_end + delim_len;
      tkns.push_back(tkn);
    }
    tkns.push_back(s.substr(p_st));
    return tkns;

  }


};