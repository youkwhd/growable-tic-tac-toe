CC = gcc
CFLAGS = -Wall

BIN = tictactoe
SRC = tictactoe.c board.c
OBJ = $(SRC:.c=.o)

all: tictactoe

tictactoe: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) *.o
