/*

AVER Code Write Department

VEX V5 Macro Controller


*/

#include "vex.h"
#include <vector>
#include <string>

#include "mach/mach_aver_rcctl.h"
#include "mach/B_IO/mach_aver_fctl.h"


using namespace vex;
using namespace std;

class AEMacroControl{
public:
	string loadedMacro_action_name = ""; // Holds macro identifier
  string loadedMacro_time_name = ""; // Holds macro identifier
	vector<string> loadedMacro_action{}; // Holds macro action in order
	vector<string> loadedMacro_time{}; // Holds macro time in order

  AEFileControl macroFileControl;
  AERemoteControl rcctl;

  vector<int> encLeft = {0, 0};
  vector<int> encRight = {0, 0};
  vector<int> encBack = {0, 0};

	void loadMacro() {
    loadedMacro_action = splitStr(macroFileControl.loadString(loadedMacro_action_name), " ");
    loadedMacro_time = splitStr(macroFileControl.loadString(loadedMacro_time_name), " ");

	}

  void recordMacro() {
    encLeft = rcctl.encLeft;
    encRight = rcctl.encRight;
    encBack = rcctl.encBack;

    auto curLeft = encLeft.begin();
    auto curRight = encRight.begin();
    auto curBack = encBack.begin();

    while(curLeft != encLeft.end() || curRight != encRight.end() || curBack != encBack.end()){
      if(curLeft != encLeft.end()){
        ++curLeft;
      }
      if(curRight != encRight.end()){
        ++curRight;
      }
      if(curBack != encBack.end()){
        ++curBack;
      }
    }

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