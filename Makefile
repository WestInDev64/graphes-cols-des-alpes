SHELL= /bin/sh
CC= gcc
CFLAGS= -Wall -Wextra -Wpedantic
LEAK= -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address -fsanitize=undefined
PROGNAME= graph_alpes
VERSION= 1.2.3

BINDIR= bin

SRC= graph.c listeadj.c floydwarshall.c graph_parser.c
CSRC= main.c $(SRC)

OBJDIR= obj
_OBJ= $(CSRC:.c=.o)
OBJ= $(addprefix $(OBJDIR)/, $(_OBJ))

all: $(PROGNAME)

dev:
	$(CC) $(CFLAGS) $(LEAK) -g $(CSRC)

$(PROGNAME): $(OBJ) $(BINDIR)
	$(CC) $(OBJ) -o $(BINDIR)/$(PROGNAME)

$(OBJDIR)/%.o: %.c $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

clean:
	@rm -rf $(OBJDIR) $(BINDIR) *.out *.dSYM
