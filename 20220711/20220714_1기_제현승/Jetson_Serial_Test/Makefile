CFLAGS = -w -Wall -O2
SRCS = serial.c  -lpthread
PROG = test
OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)
$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
	$(./PROG)
