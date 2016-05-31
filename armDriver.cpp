#include "armDriver.h"

uint8_t* ArmDriver::moveArm(MotionType motionType, Action action, float startVelocity){
    dataBuffer[0] = 0xA5;
    dataBuffer[41] = 0x5A;
    float floatData;
    floatData = motionType;
    memcpy(&dataBuffer[MOTION_TYPE_INDEX], &floatData, sizeof(float) );
    floatData = action;
    memcpy(&dataBuffer[ACTION_INDEX], &floatData, sizeof(float) );
    floatData = startVelocity;
    memcpy(&dataBuffer[START_VELOCITY_INDEX], &floatData, sizeof(float) );
    return dataBuffer;
}

uint8_t* ArmDriver::getDataBytes(){
    return dataBuffer;
}

uint8_t* ArmDriver::moveToPosition(ArmDataBuffer armDataBuffer){
    dataBuffer[0] = 0xA5;
    dataBuffer[41] = 0x5A;
    memcpy(&dataBuffer[1], &armDataBuffer, sizeof(armDataBuffer));
    return dataBuffer;
}