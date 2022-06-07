CC = gcc
CFLAGS = -Wall

BIN = tictactoe
SRC = tictactoe.c board.c
OBJ = tictactoe.o board.o
DEPS = board.h

all: tictactoe

tictactoe: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) *.o
