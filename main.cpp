#include <iostream>
#include <stdint.h>
#include "armData.h"
#include "uart.h"

int main(int argc, char * args[]){
    int portDescriptor;
    ArmDataBuffer armDataBuffer;

    if ( argc < 2 ){
        cerr <<"You must specify the serial port name"<<endl;
        cerr <<"exampl : ./main /dev/ttyACM0"<<endl;
        return 0;
    }

    cout << "Initialize " << args[1] << "... ";
    portDescriptor = Uart::initUart(args[1], __9600, DATA_8_BIT, STOP_1_BIT, NO_PARITY);
    cout << "[SUCCESS]" << endl;

    uint8_t buffer[1];
    bool isReadingData = false;
    uint8_t index;
    while(read(portDescriptor,buffer,1)){
        if ( buffer[0] == ArmData::HEADER){
            isReadingData = true;
            index = 0;
        }
        else if (buffer[0] == ArmData::FOOTER){
            isReadingData = false;
        }
        else{
            if (isReadingData){
                armDataBuffer.rawBytes[index++] = buffer[0];
                if ( index == sizeof(armDataBuffer) ){
                    break;
                }
            }
        }
    }

    ArmData armData(armDataBuffer);
    cout << armData.toString() << endl;

    return 0;
}