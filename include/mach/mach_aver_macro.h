/*

AVER Code Write Department

VEX V5 Macro Controller


*/

#include "vex.h"
#include <vector>
#include <string>




using namespace vex;
using namespace std;

class AEMacroControl{
public:
	string loadedMacro_action_name = ""; // Holds macro identifier
	string loadedMacro_time_name = ""; // Holds macro identifier
	vector<string> loadedMacro_action{}; // Holds macro action in order
	vector<string> loadedMacro_time{}; // Holds macro time in order

	void recordMacro(AERemoteControl rcctl, string fileName, AEFileControl fctl) {
		string encoderLeft = join(rcctl.encLeft);
		string encoderRight = join(rcctl.encRight);
		string encoderBack = join(rcctl.encBack);
		
		fctl.saveString(fileName + "_enc_Left", encoderLeft);
		fctl.saveString(fileName + "_enc_Right", encoderRight);
		fctl.saveString(fileName + "_enc_Back", encoderBack);
	}

	string join(vector<int> vect) {
		string str = "";
		
		for(short i = 0; i < vect.size(); i++) str += vect.at(i);
		return str;
	}

	void loadMacro(AEFileControl macroFileControl, string loadedMacro_name) {
		loadedMacro_action = splitStr(macroFileControl.loadString(loadedMacro_name) + "_action", " ");
		loadedMacro_time = splitStr(macroFileControl.loadString(loadedMacro_name + "_time"), " ");

		auto curAction = loadedMacro_action.begin();
		auto curTime = loadedMacro_time.begin();

		while(curAction != loadedMacro_action.end() || curTime != loadedMacro_time.end()){
			if(curAction != loadedMacro_action.end()) ++curAction;
			if(curTime != loadedMacro_time.end()) ++curTime;
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