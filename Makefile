CC=gcc
CFLAGS=-lX11 -lGL -lGLU -lvdpau

sample: sample.c
	$(CC) -o sample sample.c  $(CFLAGS)


