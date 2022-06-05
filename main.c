#include <stdio.h>

#define PLAYER_1 'X'
#define PLAYER_2 'O'

#define BOARD_ROWS 3
#define BOARD_COLS 3

/* how many tiles to check
 * the classic checks for only 3 tiles.
 */
#define BOARD_CHECK_RANGE 3 

void init_board(int rows, int cols, int board[rows][cols]);
void draw_board(int rows, int cols, int board[rows][cols]);
void get_input(int rows, int cols, int board[rows][cols], char player);
int is_board_has_space(int rows, int cols, int board[rows][cols]);
int check_game_winner(int rows, int cols, int board[rows][cols]);
int check_player_position(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_horizontal(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_vertical(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_diagonal(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_diagonal_reverse(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);

int main(int argc, char **argv) {
	int board[BOARD_ROWS][BOARD_COLS];
	int x, y;
	int game_over = 0;
	int player_turn = 1; // who's turn not how many turns.

	init_board(BOARD_ROWS, BOARD_COLS, board);
	draw_board(BOARD_ROWS, BOARD_COLS, board);
	printf("\n");

	while (!game_over) {
		if (!is_board_has_space(BOARD_ROWS, BOARD_COLS, board)) {
			printf("no one wins!\n");
			game_over = 1;

			break;
		}

		printf("player %d's turn\ninput: ", player_turn);
		scanf("%d %d", &x, &y);

		switch (player_turn) {
			case 1:
				/* this will occur when the player hits a space that is not empty
				 * meaning that it has been marked by someone before.
				 *
				 * OR when the player missed input the coordinate and it's "out-of-index".
				 * 
				 * thus will reset the player's turn to redo it's move once more,
				 * until the player marked an empty space.
				 *
				 * same applies with other players.
				 */
				if (board[x][y] != ' ') {
					break;
				}

				board[x][y] = PLAYER_1;
				player_turn++;
				break;
			case 2:
				if (board[x][y] != ' ') {
					break;
				}

				board[x][y] = PLAYER_2;
				/* reset to the first player in order to cycle
				 *
				 * NOTE: if you want to add more player, increment `player_turn`
				 * append the same `player_turn = 1` to the last player so it can cycle.
				 */
				player_turn = 1;
				break;
		}

		draw_board(BOARD_ROWS, BOARD_COLS, board);
		printf("\n");

		int player_winner_num = check_game_winner(BOARD_ROWS, BOARD_COLS, board);
		if (player_winner_num) {
			printf("player %d won!\n", player_winner_num);
			game_over = 1;

			break;
		}
	}

	return 0;
}

/* initialize the board with spaces
 */
void init_board(int rows, int cols, int board[rows][cols]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j] = ' ';
		}
	}
}

/* draws the board with a coordinate
 * for player to use when inserting inputs
 */
void draw_board(int rows, int cols, int board[rows][cols]) {
	printf("\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf(" %c |", board[i][j]);
		}
		printf("   [%d]\n", i);
	}

	printf("\n");

	for (int i = 0; i < cols; i++) {
		printf("[%d] ", i);
	}

	printf("\n");
}

/* checks the board if it has any space left.
 * 1 for ok, 0 for none.
 */
int is_board_has_space(int rows, int cols, int board[rows][cols]) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (board[i][j] == ' ') {
				return 1;
			}
		}
	}

	return 0;
}

/* checks if a player has won
 */
int check_game_winner(int rows, int cols, int board[rows][cols]) {
	int player_has_won = 0;

	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < cols; j++) {
			/* using `switch` just because i need to 
			 * correct which player won.
			 */
			switch (board[i][j]) {
				case PLAYER_1:
					player_has_won = check_player_position(BOARD_ROWS, BOARD_COLS, board, i, j, board[i][j], BOARD_CHECK_RANGE);

					if (player_has_won) {
						return 1;
					}

					break;
				case PLAYER_2:
					player_has_won = check_player_position(BOARD_ROWS, BOARD_COLS, board, i, j, board[i][j], BOARD_CHECK_RANGE);

					if (player_has_won) {
						return 2;
					}

					break;
			}
		}
	}

	return 0;
}

/* checks for the current position passed by the program 
 * for every possible solutions.
 *
 * 1 -> found winner, 0 -> no winner found
 */
int check_player_position(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range) {
	int (*check_func[4])(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range) = {
		check_player_position_horizontal,
		check_player_position_vertical,
		check_player_position_diagonal,
		check_player_position_diagonal_reverse
	};

	for (int i = 0; i < 4; i++) {
		int found_solution = check_func[i](rows, cols, board, curr_row, curr_col, player, check_range);
		if (found_solution) return 1; 
	}

	return 0;
}

/* this function will check horizontally.
 *
 * ex:
 *
 * -- starts here
 * V
 * X | X | X |   
 *   |   |   |   
 *   |   |   |   
 */
int check_player_position_horizontal(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range) {
	for (int i = 0; i < check_range; i++) { 
		/* checks if array selection is out-of-index, and
		 * also checking if next tile is player or not
		 */
		if (curr_col + i >= cols || board[curr_row][curr_col + i] != player) {
			return 0;
		}
	}

	return 1;
}

/* this function will check vertically.
 *
 * ex:
 *
 *   |   | X |   <- starts here
 *   |   | X |   
 *   |   | X |   
 */
int check_player_position_vertical(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range) {
	for (int i = 0; i < check_range; i++) { 
		/* checks if array selection is out-of-index, and
		 * also checking if next tile is player or not
		 */
		if (curr_row + i >= rows || board[curr_row + i][curr_col] != player) {
			return 0;
		}
	}

	return 1;
}

/* this function will check diagonally.
 *
 * ex:
 *
 * -- starts here
 * V
 * X |   |   |   
 *   | X |   |   
 *   |   | X |   
 */
int check_player_position_diagonal(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range) {
	for (int i = 0; i < check_range; i++) { 
		/* checks if array selection is out-of-index, and
		 * also checking if next tile is player or not
		 */
		if ((curr_row + i >= rows || curr_col + i >= cols) || (board[curr_row + i][curr_col + i] != player)) {
			return 0;
		}
	}

	return 1;
}

/* this function will check diagonally BUT in reverse.
 *
 * ex:
 *
 *   |   | X |   <- starts here
 *   | X |   |   
 * X |   |   |   
 */
int check_player_position_diagonal_reverse(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range) {
	for (int i = 0; i < check_range; i++) { 
		/* checks if array selection is out-of-index, and
		 * also checking if next tile is player or not
		 */
		if ((curr_row + i >= rows || curr_col - i < 0) || (board[curr_row + i][curr_col - i] != player)) {
			return 0;
		}
	}

	return 1;
}
