CC = g++

CFLAGS = -w -Wall -O2
SRCS = gpio_test.c Jeston_nano_GPIO.o

PROG = test

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) 
	
Jeston_nano_GPIO.o:gpio_test.c Jeston_nano_GPIO.h	
	$(CC) -c gpio_test.c
	
	$(./PROG)
