#include <bits/stdc++.h>
#include <functional>
#include "CustomVM.h"

using namespace std;

CustomVM::CustomVM() {
    ram = (char *)malloc(1000);
    initInstructionsMap();
}

int CustomVM::getReg1() {
    return reg1;
}

void CustomVM::setReg1(int reg1) {
    this->reg1 = reg1;
}

int CustomVM::getReg2() {
    return reg2;
}

void CustomVM::setReg2(int reg2) {
    this->reg2 = reg2;
}

int CustomVM::getReg3() {
    return reg3;
}

void CustomVM::setReg3(int reg3) {
    this->reg3 = reg3;
}

int CustomVM::getReg4() {
    return reg4;
}

void CustomVM::setReg4(int reg4) {
    this->reg4 = reg4;
}

int CustomVM::getReg5() {
    return reg5;
}

void CustomVM::setReg5(int reg5) {
    this->reg5 = reg5;
}

int CustomVM::getReg6() {
    return reg6;
}

void CustomVM::setReg6(int reg6) {
    this->reg6 = reg6;
}

int CustomVM::getRip() {
    return rip;
}

void CustomVM::setRip(int rip) {
    this->rip = rip;
}

int CustomVM::getDp() {
    return dp;
}

void CustomVM::setDp(int dp) {
    this->dp = dp;
}

bool CustomVM::getZFlag() {
    return zflag;
}

void CustomVM::setZFlag(bool zFlag) {
    this->zflag = zFlag;
}

char* CustomVM::getRam() {
    return this->ram;
}

void CustomVM::setRam(char* input) {
    memcpy(this->ram, input, strlen(input) + 1);
}

vector<int> CustomVM::getInstructions() {
    return this->instructions;
}

void CustomVM::setInstructions(vector<int> instructions) {
    this->instructions = instructions;
}

bool CustomVM::execute(vector<int> instructions) {
    this->setInstructions(instructions);
    int rip = 1;
    int start = instructions[0];
    this->setRip(rip);
    bool found = false;

    while(rip < instructions.size() - 1) {
        if(instructions[rip] == start && !found) {
            found = true;
        }
        if(found) {
            instructionsMap[instructions[rip]](instructions[rip + 1], instructions[rip + 2]);
            rip = this->getRip();
        } else {
            rip++;
            this->setRip(rip);
        }
    }

    return this->getZFlag() && strlen(this->getRam()) == instructions[instructions.size() - 1];
}

void CustomVM::initInstructionsMap() {

    // mov instruction with registers
    instructionsMap[100] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setReg1(this->getReg2());
            if(reg2 == 204) this->setReg1(this->getReg3());
            if(reg2 == 205) this->setReg1(this->getReg4());
            if(reg2 == 206) this->setReg1(this->getReg5());
            if(reg2 == 207) this->setReg1(this->getReg6());
            if(reg2 == 208) this->setReg1(this->getDp());
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setReg2(this->getReg1());
            if(reg2 == 204) this->setReg2(this->getReg3());
            if(reg2 == 205) this->setReg2(this->getReg4());
            if(reg2 == 206) this->setReg2(this->getReg5());
            if(reg2 == 207) this->setReg2(this->getReg6());
            if(reg2 == 208) this->setReg2(this->getDp());
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setReg3(this->getReg1());
            if(reg2 == 203) this->setReg3(this->getReg2());
            if(reg2 == 205) this->setReg3(this->getReg4());
            if(reg2 == 206) this->setReg3(this->getReg5());
            if(reg2 == 207) this->setReg3(this->getReg6());
            if(reg2 == 208) this->setReg3(this->getDp());
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setReg4(this->getReg1());
            if(reg2 == 203) this->setReg4(this->getReg2());
            if(reg2 == 204) this->setReg4(this->getReg3());
            if(reg2 == 206) this->setReg4(this->getReg5());
            if(reg2 == 207) this->setReg4(this->getReg6());
            if(reg2 == 208) this->setReg4(this->getDp());
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setReg5(this->getReg1());
            if(reg2 == 203) this->setReg5(this->getReg2());
            if(reg2 == 204) this->setReg5(this->getReg3());
            if(reg2 == 205) this->setReg5(this->getReg4());
            if(reg2 == 207) this->setReg5(this->getReg6());
            if(reg2 == 208) this->setReg5(this->getDp());
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setReg6(this->getReg1());
            if(reg2 == 203) this->setReg6(this->getReg2());
            if(reg2 == 204) this->setReg6(this->getReg3());
            if(reg2 == 205) this->setReg6(this->getReg4());
            if(reg2 == 206) this->setReg6(this->getReg5());
            if(reg2 == 208) this->setReg6(this->getDp());
        } else if(reg1 == 208) {
            if(reg2 == 202) this->setDp(this->getReg1());
            if(reg2 == 203) this->setDp(this->getReg2());
            if(reg2 == 204) this->setDp(this->getReg3());
            if(reg2 == 205) this->setDp(this->getReg4());
            if(reg2 == 206) this->setDp(this->getReg5());
            if(reg2 == 207) this->setDp(this->getReg6());
        }
        this->setRip(this->getRip() + 3);
    };

    // mov instruction with values
    instructionsMap[101] = [&](int reg1, int value) -> void {
        if(reg1 == 202) {
            this->setReg1(value);
        } else if(reg1 == 203) {
            this->setReg2(value);
        } else if(reg1 == 204) {
            this->setReg3(value);
        } else if(reg1 == 205) {
            this->setReg4(value);
        } else if(reg1 == 206) {
            this->setReg5(value);
        } else if(reg1 == 207) {
            this->setReg6(value);
        } else if(reg1 == 208) {
            this->setDp(value);
        }
        this->setRip(this->getRip() + 3);
    };

    // add instruction
    instructionsMap[102] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setReg1(this->getReg1() + this->getReg2());
            if(reg2 == 204) this->setReg1(this->getReg1() + this->getReg3());
            if(reg2 == 205) this->setReg1(this->getReg1() + this->getReg4());
            if(reg2 == 206) this->setReg1(this->getReg1() + this->getReg5());
            if(reg2 == 207) this->setReg1(this->getReg1() + this->getReg6());
            if(reg2 == 208) this->setReg1(this->getReg1() + this->getDp());
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setReg2(this->getReg2() + this->getReg1());
            if(reg2 == 204) this->setReg2(this->getReg2() + this->getReg3());
            if(reg2 == 205) this->setReg2(this->getReg2() + this->getReg4());
            if(reg2 == 206) this->setReg2(this->getReg2() + this->getReg5());
            if(reg2 == 207) this->setReg2(this->getReg2() + this->getReg6());
            if(reg2 == 208) this->setReg2(this->getReg2() + this->getDp());
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setReg3(this->getReg3() + this->getReg1());
            if(reg2 == 203) this->setReg3(this->getReg3() + this->getReg2());
            if(reg2 == 205) this->setReg3(this->getReg3() + this->getReg4());
            if(reg2 == 206) this->setReg3(this->getReg3() + this->getReg5());
            if(reg2 == 207) this->setReg3(this->getReg3() + this->getReg6());
            if(reg2 == 208) this->setReg3(this->getReg3() + this->getDp());
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setReg4(this->getReg4() + this->getReg1());
            if(reg2 == 203) this->setReg4(this->getReg4() + this->getReg2());
            if(reg2 == 204) this->setReg4(this->getReg4() + this->getReg3());
            if(reg2 == 206) this->setReg4(this->getReg4() + this->getReg5());
            if(reg2 == 207) this->setReg4(this->getReg4() + this->getReg6());
            if(reg2 == 208) this->setReg4(this->getReg4() + this->getDp());
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setReg5(this->getReg5() + this->getReg1());
            if(reg2 == 203) this->setReg5(this->getReg5() + this->getReg2());
            if(reg2 == 204) this->setReg5(this->getReg5() + this->getReg3());
            if(reg2 == 205) this->setReg5(this->getReg5() + this->getReg4());
            if(reg2 == 207) this->setReg5(this->getReg5() + this->getReg6());
            if(reg2 == 208) this->setReg5(this->getReg5() + this->getDp());
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setReg6(this->getReg6() + this->getReg1());
            if(reg2 == 203) this->setReg6(this->getReg6() + this->getReg2());
            if(reg2 == 204) this->setReg6(this->getReg6() + this->getReg3());
            if(reg2 == 205) this->setReg6(this->getReg6() + this->getReg4());
            if(reg2 == 206) this->setReg6(this->getReg6() + this->getReg5());
            if(reg2 == 208) this->setReg6(this->getReg6() + this->getDp());
        } else if(reg1 == 208) {
            if(reg2 == 202) this->setDp(this->getDp() + this->getReg1());
            if(reg2 == 203) this->setDp(this->getDp() + this->getReg2());
            if(reg2 == 204) this->setDp(this->getDp() + this->getReg3());
            if(reg2 == 205) this->setDp(this->getDp() + this->getReg4());
            if(reg2 == 206) this->setDp(this->getDp() + this->getReg5());
            if(reg2 == 207) this->setDp(this->getDp() + this->getReg6());
        }
        this->setRip(this->getRip() + 3);
    };

    // sub instruction
    instructionsMap[103] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setReg1(this->getReg1() - this->getReg2());
            if(reg2 == 204) this->setReg1(this->getReg1() - this->getReg3());
            if(reg2 == 205) this->setReg1(this->getReg1() - this->getReg4());
            if(reg2 == 206) this->setReg1(this->getReg1() - this->getReg5());
            if(reg2 == 207) this->setReg1(this->getReg1() - this->getReg6());
            if(reg2 == 208) this->setReg1(this->getReg1() - this->getDp());
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setReg2(this->getReg2() - this->getReg1());
            if(reg2 == 204) this->setReg2(this->getReg2() - this->getReg3());
            if(reg2 == 205) this->setReg2(this->getReg2() - this->getReg4());
            if(reg2 == 206) this->setReg2(this->getReg2() - this->getReg5());
            if(reg2 == 207) this->setReg2(this->getReg2() - this->getReg6());
            if(reg2 == 208) this->setReg2(this->getReg2() - this->getDp());
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setReg3(this->getReg3() - this->getReg1());
            if(reg2 == 203) this->setReg3(this->getReg3() - this->getReg2());
            if(reg2 == 205) this->setReg3(this->getReg3() - this->getReg4());
            if(reg2 == 206) this->setReg3(this->getReg3() - this->getReg5());
            if(reg2 == 207) this->setReg3(this->getReg3() - this->getReg6());
            if(reg2 == 208) this->setReg3(this->getReg3() - this->getDp());
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setReg4(this->getReg4() - this->getReg1());
            if(reg2 == 203) this->setReg4(this->getReg4() - this->getReg2());
            if(reg2 == 204) this->setReg4(this->getReg4() - this->getReg3());
            if(reg2 == 206) this->setReg4(this->getReg4() - this->getReg5());
            if(reg2 == 207) this->setReg4(this->getReg4() - this->getReg6());
            if(reg2 == 208) this->setReg4(this->getReg4() - this->getDp());
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setReg5(this->getReg5() - this->getReg1());
            if(reg2 == 203) this->setReg5(this->getReg5() - this->getReg2());
            if(reg2 == 204) this->setReg5(this->getReg5() - this->getReg3());
            if(reg2 == 205) this->setReg5(this->getReg5() - this->getReg4());
            if(reg2 == 207) this->setReg5(this->getReg5() - this->getReg6());
            if(reg2 == 208) this->setReg5(this->getReg5() - this->getDp());
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setReg6(this->getReg6() - this->getReg1());
            if(reg2 == 203) this->setReg6(this->getReg6() - this->getReg2());
            if(reg2 == 204) this->setReg6(this->getReg6() - this->getReg3());
            if(reg2 == 205) this->setReg6(this->getReg6() - this->getReg4());
            if(reg2 == 206) this->setReg6(this->getReg6() - this->getReg5());
            if(reg2 == 208) this->setReg6(this->getReg6() - this->getDp());
        } else if(reg1 == 208) {
            if(reg2 == 202) this->setDp(this->getDp() - this->getReg1());
            if(reg2 == 203) this->setDp(this->getDp() - this->getReg2());
            if(reg2 == 204) this->setDp(this->getDp() - this->getReg3());
            if(reg2 == 205) this->setDp(this->getDp() - this->getReg4());
            if(reg2 == 206) this->setDp(this->getDp() - this->getReg5());
            if(reg2 == 207) this->setDp(this->getDp() - this->getReg6());
        }
        this->setRip(this->getRip() + 3);
    };

    // mul instruction
    instructionsMap[104] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setReg1(this->getReg1() * this->getReg2());
            if(reg2 == 204) this->setReg1(this->getReg1() * this->getReg3());
            if(reg2 == 205) this->setReg1(this->getReg1() * this->getReg4());
            if(reg2 == 206) this->setReg1(this->getReg1() * this->getReg5());
            if(reg2 == 207) this->setReg1(this->getReg1() * this->getReg6());
            if(reg2 == 208) this->setReg1(this->getReg1() * this->getDp());
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setReg2(this->getReg2() * this->getReg1());
            if(reg2 == 204) this->setReg2(this->getReg2() * this->getReg3());
            if(reg2 == 205) this->setReg2(this->getReg2() * this->getReg4());
            if(reg2 == 206) this->setReg2(this->getReg2() * this->getReg5());
            if(reg2 == 207) this->setReg2(this->getReg2() * this->getReg6());
            if(reg2 == 208) this->setReg2(this->getReg2() * this->getDp());
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setReg3(this->getReg3() * this->getReg1());
            if(reg2 == 203) this->setReg3(this->getReg3() * this->getReg2());
            if(reg2 == 205) this->setReg3(this->getReg3() * this->getReg4());
            if(reg2 == 206) this->setReg3(this->getReg3() * this->getReg5());
            if(reg2 == 207) this->setReg3(this->getReg3() * this->getReg6());
            if(reg2 == 208) this->setReg3(this->getReg3() * this->getDp());
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setReg4(this->getReg4() * this->getReg1());
            if(reg2 == 203) this->setReg4(this->getReg4() * this->getReg2());
            if(reg2 == 204) this->setReg4(this->getReg4() * this->getReg3());
            if(reg2 == 206) this->setReg4(this->getReg4() * this->getReg5());
            if(reg2 == 207) this->setReg4(this->getReg4() * this->getReg6());
            if(reg2 == 208) this->setReg4(this->getReg4() * this->getDp());
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setReg5(this->getReg5() * this->getReg1());
            if(reg2 == 203) this->setReg5(this->getReg5() * this->getReg2());
            if(reg2 == 204) this->setReg5(this->getReg5() * this->getReg3());
            if(reg2 == 205) this->setReg5(this->getReg5() * this->getReg4());
            if(reg2 == 207) this->setReg5(this->getReg5() * this->getReg6());
            if(reg2 == 208) this->setReg5(this->getReg5() * this->getDp());
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setReg6(this->getReg6() * this->getReg1());
            if(reg2 == 203) this->setReg6(this->getReg6() * this->getReg2());
            if(reg2 == 204) this->setReg6(this->getReg6() * this->getReg3());
            if(reg2 == 205) this->setReg6(this->getReg6() * this->getReg4());
            if(reg2 == 206) this->setReg6(this->getReg6() * this->getReg5());
            if(reg2 == 208) this->setReg6(this->getReg6() * this->getDp());
        } else if(reg1 == 208) {
            if(reg2 == 202) this->setDp(this->getDp() * this->getReg1());
            if(reg2 == 203) this->setDp(this->getDp() * this->getReg2());
            if(reg2 == 204) this->setDp(this->getDp() * this->getReg3());
            if(reg2 == 205) this->setDp(this->getDp() * this->getReg4());
            if(reg2 == 206) this->setDp(this->getDp() * this->getReg5());
            if(reg2 == 207) this->setDp(this->getDp() * this->getReg6());
        }
        this->setRip(this->getRip() + 3);
    };

    // div instruction
    instructionsMap[105] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setReg1(this->getReg1() / this->getReg2());
            if(reg2 == 204) this->setReg1(this->getReg1() / this->getReg3());
            if(reg2 == 205) this->setReg1(this->getReg1() / this->getReg4());
            if(reg2 == 206) this->setReg1(this->getReg1() / this->getReg5());
            if(reg2 == 207) this->setReg1(this->getReg1() / this->getReg6());
            if(reg2 == 208) this->setReg1(this->getReg1() / this->getDp());
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setReg2(this->getReg2() / this->getReg1());
            if(reg2 == 204) this->setReg2(this->getReg2() / this->getReg3());
            if(reg2 == 205) this->setReg2(this->getReg2() / this->getReg4());
            if(reg2 == 206) this->setReg2(this->getReg2() / this->getReg5());
            if(reg2 == 207) this->setReg2(this->getReg2() / this->getReg6());
            if(reg2 == 208) this->setReg2(this->getReg2() / this->getDp());
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setReg3(this->getReg3() / this->getReg1());
            if(reg2 == 203) this->setReg3(this->getReg3() / this->getReg2());
            if(reg2 == 205) this->setReg3(this->getReg3() / this->getReg4());
            if(reg2 == 206) this->setReg3(this->getReg3() / this->getReg5());
            if(reg2 == 207) this->setReg3(this->getReg3() / this->getReg6());
            if(reg2 == 208) this->setReg3(this->getReg3() / this->getDp());
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setReg4(this->getReg4() / this->getReg1());
            if(reg2 == 203) this->setReg4(this->getReg4() / this->getReg2());
            if(reg2 == 204) this->setReg4(this->getReg4() / this->getReg3());
            if(reg2 == 206) this->setReg4(this->getReg4() / this->getReg5());
            if(reg2 == 207) this->setReg4(this->getReg4() / this->getReg6());
            if(reg2 == 208) this->setReg4(this->getReg4() / this->getDp());
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setReg5(this->getReg5() / this->getReg1());
            if(reg2 == 203) this->setReg5(this->getReg5() / this->getReg2());
            if(reg2 == 204) this->setReg5(this->getReg5() / this->getReg3());
            if(reg2 == 205) this->setReg5(this->getReg5() / this->getReg4());
            if(reg2 == 207) this->setReg5(this->getReg5() / this->getReg6());
            if(reg2 == 208) this->setReg5(this->getReg5() / this->getDp());
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setReg6(this->getReg6() / this->getReg1());
            if(reg2 == 203) this->setReg6(this->getReg6() / this->getReg2());
            if(reg2 == 204) this->setReg6(this->getReg6() / this->getReg3());
            if(reg2 == 205) this->setReg6(this->getReg6() / this->getReg4());
            if(reg2 == 206) this->setReg6(this->getReg6() / this->getReg5());
            if(reg2 == 208) this->setReg6(this->getReg6() / this->getDp());
        } else if(reg1 == 208) {
            if(reg2 == 202) this->setDp(this->getDp() / this->getReg1());
            if(reg2 == 203) this->setDp(this->getDp() / this->getReg2());
            if(reg2 == 204) this->setDp(this->getDp() / this->getReg3());
            if(reg2 == 205) this->setDp(this->getDp() / this->getReg4());
            if(reg2 == 206) this->setDp(this->getDp() / this->getReg5());
            if(reg2 == 207) this->setDp(this->getDp() / this->getReg6());
        }
        this->setRip(this->getRip() + 3);
    };

    // cmp instruction
    instructionsMap[106] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setZFlag(this->getReg1() == this->getReg2());
            if(reg2 == 204) this->setZFlag(this->getReg1() == this->getReg3());
            if(reg2 == 205) this->setZFlag(this->getReg1() == this->getReg4());
            if(reg2 == 206) this->setZFlag(this->getReg1() == this->getReg5());
            if(reg2 == 207) this->setZFlag(this->getReg1() == this->getReg6());
            if(reg2 == 208) this->setZFlag(this->getReg1() == this->getDp());
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setZFlag(this->getReg2() == this->getReg1());
            if(reg2 == 204) this->setZFlag(this->getReg2() == this->getReg3());
            if(reg2 == 205) this->setZFlag(this->getReg2() == this->getReg4());
            if(reg2 == 206) this->setZFlag(this->getReg2() == this->getReg5());
            if(reg2 == 207) this->setZFlag(this->getReg2() == this->getReg6());
            if(reg2 == 208) this->setZFlag(this->getReg2() == this->getDp());
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setZFlag(this->getReg3() == this->getReg1());
            if(reg2 == 203) this->setZFlag(this->getReg3() == this->getReg2());
            if(reg2 == 205) this->setZFlag(this->getReg3() == this->getReg4());
            if(reg2 == 206) this->setZFlag(this->getReg3() == this->getReg5());
            if(reg2 == 207) this->setZFlag(this->getReg3() == this->getReg6());
            if(reg2 == 208) this->setZFlag(this->getReg3() == this->getDp());
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setZFlag(this->getReg4() == this->getReg1());
            if(reg2 == 203) this->setZFlag(this->getReg4() == this->getReg2());
            if(reg2 == 204) this->setZFlag(this->getReg4() == this->getReg3());
            if(reg2 == 206) this->setZFlag(this->getReg4() == this->getReg5());
            if(reg2 == 207) this->setZFlag(this->getReg4() == this->getReg6());
            if(reg2 == 208) this->setZFlag(this->getReg4() == this->getDp());
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setZFlag(this->getReg5() == this->getReg1());
            if(reg2 == 203) this->setZFlag(this->getReg5() == this->getReg2());
            if(reg2 == 204) this->setZFlag(this->getReg5() == this->getReg3());
            if(reg2 == 205) this->setZFlag(this->getReg5() == this->getReg4());
            if(reg2 == 207) this->setZFlag(this->getReg5() == this->getReg6());
            if(reg2 == 208) this->setZFlag(this->getReg5() == this->getDp());
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setZFlag(this->getReg6() == this->getReg1());
            if(reg2 == 203) this->setZFlag(this->getReg6() == this->getReg2());
            if(reg2 == 204) this->setZFlag(this->getReg6() == this->getReg3());
            if(reg2 == 205) this->setZFlag(this->getReg6() == this->getReg4());
            if(reg2 == 206) this->setZFlag(this->getReg6() == this->getReg5());
            if(reg2 == 208) this->setZFlag(this->getReg6() == this->getDp());
        } else if(reg1 == 208) {
            if(reg2 == 202) this->setZFlag(this->getDp() == this->getReg1());
            if(reg2 == 203) this->setZFlag(this->getDp() == this->getReg2());
            if(reg2 == 204) this->setZFlag(this->getDp() == this->getReg3());
            if(reg2 == 205) this->setZFlag(this->getDp() == this->getReg4());
            if(reg2 == 206) this->setZFlag(this->getDp() == this->getReg5());
            if(reg2 == 207) this->setZFlag(this->getDp() == this->getReg6());
        }
        this->setRip(this->getRip() + 3);
    };

    // je instruction
    instructionsMap[107] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setRip(this->getZFlag() ? this->getReg1() : this->getReg2());
            if(reg2 == 204) this->setRip(this->getZFlag() ? this->getReg1() : this->getReg3());
            if(reg2 == 205) this->setRip(this->getZFlag() ? this->getReg1() : this->getReg4());
            if(reg2 == 206) this->setRip(this->getZFlag() ? this->getReg1() : this->getReg5());
            if(reg2 == 207) this->setRip(this->getZFlag() ? this->getReg1() : this->getReg6());
            if(reg2 == 208) this->setRip(this->getZFlag() ? this->getReg1() : this->getDp());
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setRip(this->getZFlag() ? this->getReg2() : this->getReg1());
            if(reg2 == 204) this->setRip(this->getZFlag() ? this->getReg2() : this->getReg3());
            if(reg2 == 205) this->setRip(this->getZFlag() ? this->getReg2() : this->getReg4());
            if(reg2 == 206) this->setRip(this->getZFlag() ? this->getReg2() : this->getReg5());
            if(reg2 == 207) this->setRip(this->getZFlag() ? this->getReg2() : this->getReg6());
            if(reg2 == 208) this->setRip(this->getZFlag() ? this->getReg2() : this->getDp());
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setRip(this->getZFlag() ? this->getReg3() : this->getReg1());
            if(reg2 == 203) this->setRip(this->getZFlag() ? this->getReg3() : this->getReg2());
            if(reg2 == 205) this->setRip(this->getZFlag() ? this->getReg3() : this->getReg4());
            if(reg2 == 206) this->setRip(this->getZFlag() ? this->getReg3() : this->getReg5());
            if(reg2 == 207) this->setRip(this->getZFlag() ? this->getReg3() : this->getReg6());
            if(reg2 == 208) this->setRip(this->getZFlag() ? this->getReg3() : this->getDp());
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setRip(this->getZFlag() ? this->getReg4() : this->getReg1());
            if(reg2 == 203) this->setRip(this->getZFlag() ? this->getReg4() : this->getReg2());
            if(reg2 == 204) this->setRip(this->getZFlag() ? this->getReg4() : this->getReg3());
            if(reg2 == 206) this->setRip(this->getZFlag() ? this->getReg4() : this->getReg5());
            if(reg2 == 207) this->setRip(this->getZFlag() ? this->getReg4() : this->getReg6());
            if(reg2 == 208) this->setRip(this->getZFlag() ? this->getReg4() : this->getDp());
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setRip(this->getZFlag() ? this->getReg5() : this->getReg1());
            if(reg2 == 203) this->setRip(this->getZFlag() ? this->getReg5() : this->getReg2());
            if(reg2 == 204) this->setRip(this->getZFlag() ? this->getReg5() : this->getReg3());
            if(reg2 == 205) this->setRip(this->getZFlag() ? this->getReg5() : this->getReg4());
            if(reg2 == 207) this->setRip(this->getZFlag() ? this->getReg5() : this->getReg6());
            if(reg2 == 208) this->setRip(this->getZFlag() ? this->getReg5() : this->getDp());
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setRip(this->getZFlag() ? this->getReg6() : this->getReg1());
            if(reg2 == 203) this->setRip(this->getZFlag() ? this->getReg6() : this->getReg2());
            if(reg2 == 204) this->setRip(this->getZFlag() ? this->getReg6() : this->getReg3());
            if(reg2 == 205) this->setRip(this->getZFlag() ? this->getReg6() : this->getReg4());
            if(reg2 == 206) this->setRip(this->getZFlag() ? this->getReg6() : this->getReg5());
            if(reg2 == 208) this->setRip(this->getZFlag() ? this->getReg6() : this->getDp());
        } else if(reg1 == 208) {
            if(reg2 == 202) this->setRip(this->getZFlag() ? this->getDp() : this->getReg1());
            if(reg2 == 203) this->setRip(this->getZFlag() ? this->getDp() : this->getReg2());
            if(reg2 == 204) this->setRip(this->getZFlag() ? this->getDp() : this->getReg3());
            if(reg2 == 205) this->setRip(this->getZFlag() ? this->getDp() : this->getReg4());
            if(reg2 == 206) this->setRip(this->getZFlag() ? this->getDp() : this->getReg5());
            if(reg2 == 207) this->setRip(this->getZFlag() ? this->getDp() : this->getReg6());
        }
    };

    // lea instruction
    instructionsMap[108] = [&](int reg1, int dp) -> void {
        if(reg1 == 202) {
            this->setReg1(this->getInstructions()[this->getDp()]);
        } else if(reg1 == 203) {
            this->setReg2(this->getInstructions()[this->getDp()]);
        } else if(reg1 == 204) {
            this->setReg3(this->getInstructions()[this->getDp()]);
        } else if(reg1 == 205) {
            this->setReg4(this->getInstructions()[this->getDp()]);
        } else if(reg1 == 206) {
            this->setReg5(this->getInstructions()[this->getDp()]);
        } else if(reg1 == 207) {
            this->setReg6(this->getInstructions()[this->getDp()]);
        } else if(reg1 == 208) {
            this->setDp(this->getInstructions()[this->getDp()]);
        }
        this->setRip(this->getRip() + 3);
    };

    // lfr instruction
    instructionsMap[109] = [&](int reg1, int reg2) -> void {
        if(reg1 == 202) {
            if(reg2 == 203) this->setReg1(this->getRam()[this->getReg2()]);
            if(reg2 == 204) this->setReg1(this->getRam()[this->getReg3()]);
            if(reg2 == 205) this->setReg1(this->getRam()[this->getReg4()]);
            if(reg2 == 206) this->setReg1(this->getRam()[this->getReg5()]);
            if(reg2 == 207) this->setReg1(this->getRam()[this->getReg6()]);
        } else if(reg1 == 203) {
            if(reg2 == 202) this->setReg2(this->getRam()[this->getReg1()]);
            if(reg2 == 204) this->setReg2(this->getRam()[this->getReg3()]);
            if(reg2 == 205) this->setReg2(this->getRam()[this->getReg4()]);
            if(reg2 == 206) this->setReg2(this->getRam()[this->getReg5()]);
            if(reg2 == 207) this->setReg2(this->getRam()[this->getReg6()]);
        } else if(reg1 == 204) {
            if(reg2 == 202) this->setReg3(this->getRam()[this->getReg1()]);
            if(reg2 == 203) this->setReg3(this->getRam()[this->getReg2()]);
            if(reg2 == 205) this->setReg3(this->getRam()[this->getReg4()]);
            if(reg2 == 206) this->setReg3(this->getRam()[this->getReg5()]);
            if(reg2 == 207) this->setReg3(this->getRam()[this->getReg6()]);
        } else if(reg1 == 205) {
            if(reg2 == 202) this->setReg4(this->getRam()[this->getReg1()]);
            if(reg2 == 203) this->setReg4(this->getRam()[this->getReg2()]);
            if(reg2 == 204) this->setReg4(this->getRam()[this->getReg3()]);
            if(reg2 == 206) this->setReg4(this->getRam()[this->getReg5()]);
            if(reg2 == 207) this->setReg4(this->getRam()[this->getReg6()]);
        } else if(reg1 == 206) {
            if(reg2 == 202) this->setReg5(this->getRam()[this->getReg1()]);
            if(reg2 == 203) this->setReg5(this->getRam()[this->getReg2()]);
            if(reg2 == 204) this->setReg5(this->getRam()[this->getReg3()]);
            if(reg2 == 205) this->setReg5(this->getRam()[this->getReg4()]);
            if(reg2 == 207) this->setReg5(this->getRam()[this->getReg6()]);
        } else if(reg1 == 207) {
            if(reg2 == 202) this->setReg6(this->getRam()[this->getReg1()]);
            if(reg2 == 203) this->setReg6(this->getRam()[this->getReg2()]);
            if(reg2 == 204) this->setReg6(this->getRam()[this->getReg3()]);
            if(reg2 == 205) this->setReg6(this->getRam()[this->getReg4()]);
            if(reg2 == 206) this->setReg6(this->getRam()[this->getReg5()]);
        }
        this->setRip(this->getRip() + 3);
    };
}