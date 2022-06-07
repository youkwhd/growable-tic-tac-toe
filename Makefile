CC = gcc
CFLAGS = -Wall

SRC = tictactoe.c board.c
OBJ = tictactoe.o board.o
DEPS = board.h

all: tictactoe

tictactoe: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# TODO: header file causes all files to recompile
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf tictactoe *.o
