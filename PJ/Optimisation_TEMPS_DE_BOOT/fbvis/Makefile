CC = /home/texierp/Documents/segment_SOL/crosstool-chain/gcc-linaro-arm-linux-gnueabihf-4.7-2013.01-20130125_linux/bin/arm-linux-gnueabihf-gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm

all: fbvis
%.o: %.c
	$(CC) -c $(CFLAGS) $<
fbvis: fbvis.o draw.o ppm.o stb_image.o lodepng.o
	$(CC) -o $@ $^ $(LDFLAGS)
clean:
	rm -f *.o fbvis
