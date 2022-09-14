CFLAGS = -w -Wall -O2
SRCS = moving_average_filter.c  -lpthread
PROG = test
OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)
$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
	$(./PROG)
