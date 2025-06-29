CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

EXEC = build/orionConsole

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c
	@if not exist build mkdir build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	-del /Q build\*.o build\*.exe
else
	rm -f build/*.o $(EXEC)
endif
