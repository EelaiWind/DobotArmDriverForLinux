#ifndef _H_ARM_DRIVER
#define _H_ARM_DRIVER

#include <cstdlib>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <sstream>
#include <errno.h>
#include "uart.h"

#define PROTOCOL_DATA_SIZE 40

enum MotionType{
    AXIS = 2,
    //COORDINATE_POSITION = 3,
    //ANGULAR_POSITION = 6,
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

typedef union _ProtoclData
{
    uint8_t bytes[PROTOCOL_DATA_SIZE];
    float floatData[PROTOCOL_DATA_SIZE/sizeof(float)];
} ProtoclData;


typedef struct _ArmStatus
{
    float coordinateX;
    float coordinateY;
    float coordinateZ;
    float headRotation;
    float baseAngle;
    float rearArmAngle;
    float foreArmAngle;
    float servoAngle;
    float isGrabbed;
    float gripperAngle;
} ArmStatus;

class ArmDriver{
public:
    ArmDriver(char *);
    void connectToArm();
    void changeArmStatus();
    void changeArmStatus(MotionType motionType, Action action, float startVelocity);
    ArmStatus getArmStatus();
    static string getArmDataString(ArmStatus armStatus);

private:
    const static uint8_t PROTOCOL_HEADER = 0xA5;
    const static uint8_t PROTOCOL_FOOTER = 0x5A;

    int portDescriptor;
    ArmStatus armStatus;
    ProtoclData actionData;

    pthread_t serialPortReaderThread;
    pthread_t serialPortWriterThread;
    pthread_mutex_t serialPortReaderMutex;
    pthread_mutex_t serialPortWriterMutex;

    static void *readSerialPort(void *arg);
    static void *writeSerialPort(void *arg);
    void initArmStatus();
};

#endif