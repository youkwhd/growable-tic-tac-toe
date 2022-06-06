#include <stdio.h>
#include "tic_tac_toe.h"

int main(int argc, char **argv) {
	int board[BOARD_ROWS][BOARD_COLS];
	int game_over = 0;

	init_board(BOARD_ROWS, BOARD_COLS, board);
	draw_board(BOARD_ROWS, BOARD_COLS, board);
	printf("\n");

	while (!game_over) {
		if (!is_board_has_space(BOARD_ROWS, BOARD_COLS, board)) {
			printf("no one wins!\n");
			game_over = 1;

			break;
		}

		get_player_input_and_mark_tile(BOARD_ROWS, BOARD_COLS, board);
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
