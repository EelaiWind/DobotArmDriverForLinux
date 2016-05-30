#ifndef _H_UART
#define _H_UART

#include <stdint.h>
#include <iostream>
#include <cstdio>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

using namespace std;

enum BaudRate {
	__9600 = B9600
};
enum DataBit {
	DATA_5_BIT = CS5,
	DATA_6_BIT = CS6,
	DATA_7_BIT = CS7,
	DATA_8_BIT = CS8
};

enum StopBit {
	STOP_1_BIT,
	STOP_2_BIT
};

enum Parity {
	NO_PARITY,
	ODD_PARITY,
	EVEN_PARITY
};

class Uart {

public:
	static int initUart(char *portDescriptor, BaudRate baudRate, DataBit dataBit, StopBit stopBit, Parity parity);

private:
	static int openSerialPort(char *portName);
	static void setDataBits(termios &options, DataBit dataBit);
	static void setParity(termios &options, Parity parity);
	static void setStopBit(termios &options, StopBit stopBit);
	static void setRawDataMode(termios &options);
};

#endif
