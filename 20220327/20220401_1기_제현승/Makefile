CC = g++

CFLAGS = -w -Wall -O2
SRCS = 20220401_1기_제현승.cpp  

PROG = 20220401_1기_제현승

OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS) -lpthread

	$(./PROG)
