CC = gcc
CFLAGS = -g -Wall

BIN = tictactoe
SRC = tictactoe.c board.c
OBJ = $(SRC:.c=.o)

all: tictactoe

tictactoe: $(OBJ)
	@echo "[DEBUG] linking all objects into binary"
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	@echo "[DEBUG] generating object files"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) *.o
