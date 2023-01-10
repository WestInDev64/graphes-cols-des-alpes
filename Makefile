SHELL= /bin/sh
CC= gcc
CFLAGS= -Wall -Wextra -Wpedantic
LEAK= -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address -fsanitize=undefined
PROGNAME= graph_alpes
VERSION= 1.2.3
CSRC= main.c graph.c listeadj.c floydwarshall.c
#HSRC=
OBJ= $(CSRC:.c=.o)


all: $(PROGNAME)

dev:
	$(CC) $(CFLAGS) $(LEAK) -g $(CSRC)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -rf $(OBJ) $(PROGNAME) *.out *.dSYM
