#include <iostream>
#include <stdint.h>
#include "armData.h"
#include "armDriver.h"
#include "uart.h"
#include <pthread.h>

ArmDriver armDriver;
pthread_mutex_t mutex;

void * thread_function(void *arg);

int main(int argc, char * args[]){
    pthread_t thread_id;

    if ( argc < 2 ){
        cerr <<"You must specify the serial port name"<<endl;
        cerr <<"exampl : ./main /dev/ttyACM0"<<endl;
        return 0;
    }

    pthread_create(&thread_id, NULL, thread_function, (void *)(args[1]) ); //~ 创建新线程
    pthread_mutex_init(&mutex, NULL);

    int action;
    ArmDataBuffer positionRecord;
    positionRecord.data[0] = 3;
    positionRecord.data[1] = 0;
    positionRecord.data[2] = 231.94;
    positionRecord.data[3] = 186.419;
    positionRecord.data[4] = -98.7411;
    positionRecord.data[5] = 38.79;
    positionRecord.data[6] = 1;
    positionRecord.data[7] = 2;
    positionRecord.data[8] = 0;
    positionRecord.data[9] = 0;

    while (1){
        scanf("%d", &action);
        cout << "Setting..." << action << endl;
        if ( action>=0 && action <= 11){
            pthread_mutex_lock(&mutex);
            armDriver.moveArm(AXIS, (Action)action, 50);
            pthread_mutex_unlock(&mutex);
        }
        else{
            pthread_mutex_lock(&mutex);
            uint8_t *ptr = armDriver.moveToPosition(positionRecord);
            ArmDataBuffer armDataBuffer;
            memcpy(armDataBuffer.rawBytes, ptr+1, sizeof(armDataBuffer));
            cout << ArmData(armDataBuffer).toString() << endl;
            pthread_mutex_unlock(&mutex);
        }
    }

    return 0;
}

void * thread_function(void *arg){
    //ArmDataBuffer armDataBuffer;
    int portDescriptor;
    char *portName = (char *)arg;
    cout << "Initialize " << portName << "... ";
    portDescriptor = Uart::initUart(portName, __9600, DATA_8_BIT, STOP_1_BIT, NO_PARITY);
    cout << "[SUCCESS]" << endl;

    while(1){
        pthread_mutex_lock(&mutex);
        uint8_t* ptr = armDriver.getDataBytes();
        pthread_mutex_unlock(&mutex);
        //memcpy(armDataBuffer.rawBytes, ptr+1, sizeof(armDataBuffer));
        //cout << ArmData(armDataBuffer).toString() << endl;
        int n = write(portDescriptor, ptr, ArmDriver::BUFFER_SIZE);
        sleep(1);
        printf("write %d bytes\n",n);
    }
    pthread_exit(NULL);
}