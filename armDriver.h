#ifndef _H_ARM_DRIVER
#define _H_ARM_DRIVER

#include <stdint.h>
#include <string.h>
#include "armData.h"

enum MotionType{
    AXIS = 2,
    COORDINATE_POSITION = 3,
    ANGULAR_POSITION = 6,
    LINEAR = 7
};

enum Action {
    IDLE = 0,
    BASE_JOINT_PLUS = 1,
    X_PLUS = 1,
    BASE_JOINT_MINUS = 2,
    X_MINUS = 2,
    REAR_JOINT_PLUS = 3,
    Y_PLUS = 3,
    REAR_JOINT_MINUS = 4,
    Y_MINUS = 4,
    FORE_JOINT_PLUS = 5,
    Z_PLUS = 5,
    FORE_JOINT_MINUS = 6,
    Z_MINUS = 6,
    SERVO_PLUS = 7,
    SERVO_MINUS = 8,
    PUMP_ON = 9,
    PUMP_OFF = 10,
    GRIPPER_OPEN = 11,
    GRIPPER_CLOSE = 12,
    LASER_ON = 13,
    LASER_OF0F = 14,
};

class ArmDriver{
public:
    const static uint8_t BUFFER_SIZE = 42;
    ArmDriver()
    :motionType(AXIS)
    ,action(IDLE)
    {
        memset(dataBuffer, 0, sizeof(dataBuffer[0])*BUFFER_SIZE);
    };
    uint8_t* moveArm(MotionType motionType, Action Action, float startVelocity);
    uint8_t* getDataBytes();
    uint8_t* moveToPosition(ArmDataBuffer armDataBuffer);
private:
    const static uint8_t MOTION_TYPE_INDEX = 1;
    const static uint8_t ACTION_INDEX = 5;
    const static uint8_t START_VELOCITY_INDEX = 29;
    uint8_t dataBuffer[BUFFER_SIZE];
    MotionType motionType;
    Action action;
};

#endif