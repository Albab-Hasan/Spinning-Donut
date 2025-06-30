CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

all: donut donut_commented donut_customizable

donut: donut.c
	$(CC) $(CFLAGS) -o donut donut.c $(LDFLAGS)

donut_commented: donut_commented.c
	$(CC) $(CFLAGS) -o donut_commented donut_commented.c $(LDFLAGS)

donut_customizable: donut_customizable.c
	$(CC) $(CFLAGS) -o donut_customizable donut_customizable.c $(LDFLAGS)

clean:
	rm -f donut donut_commented donut_customizable

.PHONY: all clean
