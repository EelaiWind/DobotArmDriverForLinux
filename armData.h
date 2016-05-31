#ifndef _H_ARM_DATA
#define _H_ARM_DATA

#include <string>
#include <sstream>
#include <stdint.h>

using namespace std;

typedef union _ArmDataBuffer{
    uint8_t rawBytes[40];
    float data[10];
} ArmDataBuffer;

class ArmData{

public:
    const static uint8_t HEADER;
    const static uint8_t FOOTER;

    ArmData();
    ArmData(ArmDataBuffer buffer)
    :coordinatX(buffer.data[0])
    ,coordinatY(buffer.data[1])
    ,coordinatZ(buffer.data[2])
    ,baseAngle(buffer.data[4])
    ,raerArmAngle(buffer.data[5])
    ,foreArmAngle(buffer.data[6])
    ,servoAngle(buffer.data[7])
    ,headRoation(buffer.data[3])
    ,gripperAngle(buffer.data[9])
    ,pumpState(buffer.data[8])
    ,startVelocity(50)
    {

    };

    string toString();
private:
    float coordinatX, coordinatY, coordinatZ;
    float baseAngle, raerArmAngle, foreArmAngle, servoAngle;
    float headRoation, gripperAngle;
    float pumpState;
    float startVelocity;
};

#endif