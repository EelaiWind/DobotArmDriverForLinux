FLAG=-Wall -O2
TARGET=main

all: ${TARGET}

main: uart.o armDriver.o main.cpp
	g++ ${FLAG} $^ -o ${TARGET} -lpthread

uart.o: uart.cpp uart.h
	g++ ${FLAG} -c $<

armDriver.o: armDriver.cpp armDriver.h
	g++ ${FLAG} -c $<

clean:
	rm *.o ${TARGET}
