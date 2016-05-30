#include "uart.h"

int Uart::initUart(char *portName, BaudRate baudRate, DataBit dataBit, StopBit stopBit, Parity parity){

	struct termios options;
	int portDescriptor;

	portDescriptor = openSerialPort(portName);
	tcgetattr(portDescriptor, &options);

	// Set baud rate
	cfsetispeed(&options, baudRate);
	cfsetospeed(&options, baudRate);

	// Enable the receiver and set local mode
	options.c_cflag |= (CLOCAL | CREAD);

	setDataBits(options, dataBit);
	setParity(options, parity);
	setStopBit(options, stopBit);
	setRawDataMode(options);

	// Apply new potions immediately
	tcsetattr(portDescriptor, TCSANOW, &options);

	return portDescriptor;
}

int Uart::openSerialPort(char *portName){
	int portDescriptor;

	portDescriptor = open(portName, O_RDWR | O_NOCTTY | O_NDELAY);
	if ( portDescriptor == -1 ){
		cerr << "openSerialPort: Unable to open port \"" << portName << "\" - "<< strerror(errno) << endl;
		throw;
	}
	else{
		fcntl(portDescriptor, F_SETFL, 0);
	}

	return portDescriptor;
}

void Uart::setDataBits(termios &options, DataBit dataBit){
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= dataBit;
}

void Uart::setParity(termios &options, Parity parity){
	switch(parity){
		case NO_PARITY:
			options.c_cflag &= ~PARENB;
			options.c_iflag &= ~INPCK;
			break;
		case EVEN_PARITY:
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD;
			options.c_iflag |= INPCK;
			break;
		case ODD_PARITY:
			options.c_cflag |= PARENB;
			options.c_cflag |= PARODD;
			options.c_iflag |= INPCK;
			break;
	}
}

void Uart::setStopBit(termios &options, StopBit stopBit){
	if ( stopBit == STOP_1_BIT ){
		options.c_cflag &= ~CSTOPB;
	}
	else{
		options.c_cflag |= CSTOPB;
	}
}

void Uart::setRawDataMode(termios &options){
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	options.c_oflag &= ~OPOST;
}