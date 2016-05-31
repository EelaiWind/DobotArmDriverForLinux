FLAG=-Wall -O2
TARGET=main
LISTENER=listener

all: ${TARGET} ${LISTENER}

main: uart.o armData.o armDriver.o main.cpp
	g++ ${FLAG} $^ -o ${TARGET} -lpthread

${LISTENER}: listener.cpp uart.o armData.o
	g++ ${FLAG} $^ -o ${LISTENER} 

uart.o: uart.cpp uart.h
	g++ ${FLAG} -c $<

armData.o: armData.cpp armData.h
	g++ ${FLAG} -c $<

armDriver.o: armDriver.cpp armDriver.h
	g++ ${FLAG} -c $<

clean:
	rm *.o ${TARGET}
