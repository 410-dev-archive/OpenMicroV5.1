#include "vex.h"
#include <string>
#include <vector>

class MRemote {
public: vector<int> encLeft;
public: vector<int> encRight;
public: vector<int> encSide;
public: vector<int> times;
public: int init_time;
public: string recentActivity;
public: string FWD;
public: string LFT;
public: bool liveControl;
public: bool updateAll(vex::controller Controller);
public: void addIndex();
public: void execute(int a, int b);
public: void onPress_startPuller2();
public: void onRelease_wheels();
public: void onPress_startPuller();
public: void onRelease_puller();
public: void onPress_systemTerminate();
};