FLAG=-Wall -O2
TARGET=main

all: ${TARGET}

main: uart.o armData.o main.cpp
	g++ ${FLAG} $^ -o ${TARGET}


uart.o: uart.cpp uart.h
	g++ ${FLAG} -c $<

armData.o: armData.cpp armData.h
	g++ ${FLAG} -c $<

clean:
	rm *.o ${TARGET}
