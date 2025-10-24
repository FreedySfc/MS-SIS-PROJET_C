CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lcrypto

SRC = src/main.c src/generate.c src/lookup.c src/hash_utils.c
OBJ = $(SRC:.c=.o)
BIN = hash_tool

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean
