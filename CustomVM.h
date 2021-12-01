#include <functional>

using namespace std;

class CustomVM {
    int reg1;
    int reg2;
    int reg3;
    int reg4;
    int reg5;
    int reg6;
    bool zflag;
    int rip;
    int dp;
    unordered_map<int, function<void(int, int)>> instructionsMap;
    char* ram;
    vector<int> instructions;

public:
    CustomVM();
    int getReg1();
    void setReg1(int reg1);
    int getReg2();
    void setReg2(int reg2);
    int getReg3();
    void setReg3(int reg3);
    int getReg4();
    void setReg4(int reg4);
    int getReg5();
    void setReg5(int reg5);
    int getReg6();
    void setReg6(int reg6);
    bool getZFlag();
    void setZFlag(bool zFlag);
    int getRip();
    void setRip(int rip);
    int getDp();
    void setDp(int dp);
    void initInstructionsMap();
    bool execute(vector<int> instructions);
    char* getRam();
    void setRam(char* input);
    vector<int> getInstructions();
    void setInstructions(vector<int> instructions);
};