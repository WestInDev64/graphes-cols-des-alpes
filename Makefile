SHELL= /bin/sh
CC= gcc
CFLAGS= -Wall -Wextra -Wpedantic
PROGNAME= graph_alpes
VERSION= 1.0.0
CSRC= main.c
#HSRC=
OBJ= $(CSRC:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean: 
	@rm -f $(OBJ) $(PROGNAME)
