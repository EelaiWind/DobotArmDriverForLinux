#include <iostream>
#include <stdint.h>
#include <cstdlib>
#include "armDriver.h"

int main(int argc, char * args[]){
    int command;
    if ( argc < 2 ){
        cerr <<"You must specify the serial port name"<<endl;
        cerr <<"exampl : ./main /dev/ttyACM0"<<endl;
        return 0;
    }
    ArmDriver armDriver(args[1]);
    armDriver.connectToArm();
    while (1){
        scanf("%d", &command);
        if ( command >=0 && command <= 10){
            armDriver.changeArmStatus(AXIS, (Action)command, 100);
        }
    }

    return 0;
}