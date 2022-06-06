#include <stdio.h>
#include "tic_tac_toe.h"

int main(int argc, char **argv) {
	char board[BOARD_ROWS][BOARD_COLS];
	int game_over = 0;

	init_board(board);
	draw_board(board);
	printf("\n");

	while (!game_over) {
		if (!is_board_has_space(board)) {
			printf("no one wins!\n");
			game_over = 1;

			break;
		}

		get_player_input_and_mark_tile(board);
		draw_board(board);
		printf("\n");

		int player_winner_num = check_game_winner(board);
		if (player_winner_num) {
			printf("player %d won!\n", player_winner_num);
			game_over = 1;

			break;
		}
	}

	return 0;
}
