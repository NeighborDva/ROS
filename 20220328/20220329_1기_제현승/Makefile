CC = g++

CFLAGS = -w -Wall -O2
SRCS = 201732049_1기_제현승.cpp  

PROG = test

OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS) -lpthread

	$(./PROG)
