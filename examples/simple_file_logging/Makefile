CC := gcc

CFLAGS := -pedantic-errors -Wall -Werror -Wextra -std=c11

SRCS := ../../clogger.c example.c

BIN := example

FILES := logs.txt

all: CFLAGS+= -O2
all: relase

debug: CFLAGS+= -O0 -g
debug: relase

relase:
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN)

clean:
	$(RM) $(BIN) $(FILES)
