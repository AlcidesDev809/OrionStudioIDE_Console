CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
CDEPENDS = -lole32 -lshell32 -luuid

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

EXEC = build/orionConsole

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(CDEPENDS)

build/%.o: src/%.c
	@if not exist build mkdir build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q build\*
