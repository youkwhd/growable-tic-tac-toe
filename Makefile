CC = gcc
CFLAGS = -Wall

SRC = tictactoe.c board.c
OBJ = tictactoe.o board.o

all: tictactoe

tictactoe: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf tictactoe *.o
