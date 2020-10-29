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


  void recordMacro() {
    encLeft = rcctl.encLeft;
    encRight = rcctl.encRight;
    encBack = rcctl.encBack;

    

  }

	void loadMacro() {
    loadedMacro_action = splitStr(macroFileControl.loadString(loadedMacro_action_name), " ");
    loadedMacro_time = splitStr(macroFileControl.loadString(loadedMacro_time_name), " ");

    auto curAction = loadedMacro_action.begin();
    auto curTime = loadedMacro_time.begin();

    while(curAction != loadedMacro_action.end() || curTime != loadedMacro_time.end()){
      if(curAction != loadedMacro_action.end()){
        ++curAction;
      }
      if(curTime != loadedMacro_time.end()){
        ++curTime;
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