#include "armData.h"

uint8_t ArmData::HEADER = 0xA5;
uint8_t ArmData::FOOTER = 0x5A;

string ArmData::toString(){
        stringstream ss;
        ss << "coordinatX = " << coordinatX <<endl;;
        ss << "coordinatY = " << coordinatY <<endl;
        ss << "coordinatZ = " << coordinatZ <<endl;
        ss << "baseAngle = " << baseAngle <<endl;
        ss << "raerArmAngle = " << raerArmAngle <<endl;
        ss << "foreArmAngle = " << foreArmAngle <<endl;
        ss << "servoAngle = " << servoAngle <<endl;
        ss << "headRoation = " << headRoation <<endl;
        ss << "gripperAngle = " << gripperAngle <<endl;
        ss << "pumpState = " << pumpState <<endl;
        return ss.str();
    };