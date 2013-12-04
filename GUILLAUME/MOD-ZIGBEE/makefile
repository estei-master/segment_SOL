CC =/home/texierp/PROJET_Drone/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf-gcc  
CFLAG = -c -Wall
EXECUTABLE = mod-zigbee
MODULES = uart

all: $(EXECUTABLE)

$(EXECUTABLE): $(MODULES).o main.o
	$(CC) $(MODULES).o main.o -o $(EXECUTABLE)

main.o: main.c
	$(CC) $(CFLAG) main.c

$(MODULES).o: $(MODULES).c
	$(CC) $(CFLAG) $(MODULES).c
	
clean:
	rm -rf *.o $(EXECUTABLE)
