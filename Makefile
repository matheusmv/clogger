CC=gcc

OBJS=clogger.c

CFLAGS=-pedantic-errors -Wall -Werror

SRC=example.c

EXE=example

all: CFLAGS+= -O2
all: relase

debug: CFLAGS+= -O0 -g
debug: relase

relase:
	$(CC) $(CFLAGS) $(OBJS) $(SRC) -o $(EXE)

clean:
	rm $(EXE)
