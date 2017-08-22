CC=gcc
CFLAGS=-lX11 -lGL -lGLU -lvdpau

test: test.c
	$(CC) -o sample sample.c  $(CFLAGS)


