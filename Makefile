CC=g++
LIBS += -lmodbus
LIBS += -lstdc++ -lmosquittopp
LIBS += -pthread    
FLAGS=-Wall -g -c 
all: modbus_ex

modbus_ex: main.o mqtt.o
	$(CC) -g main.o mqtt.o $(LIBS) -o modbus_ex
	rm -rf *.o

main.o: main.cpp
	$(CC) -c -g main.cpp

mqtt.o: mqtt/mqtt.cpp
	$(CC) -c -g mqtt/mqtt.cpp -o mqtt.o

clean:
	$(info Clean)
	@rm -rf *.o

clear:
	$(info Clear)
	@rm -rf *.o modbus_ex