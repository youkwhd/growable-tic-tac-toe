#ifndef GROWABLE_TIC_TAC_TOE_H
#define GROWABLE_TIC_TAC_TOE_H

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
void get_player_input_and_mark_tile(int rows, int cols, int board[rows][cols]);
int is_board_has_space(int rows, int cols, int board[rows][cols]);
int check_game_winner(int rows, int cols, int board[rows][cols]);
int check_player_position(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_horizontal(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_vertical(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_diagonal(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);
int check_player_position_diagonal_reverse(int rows, int cols, int board[rows][cols], int curr_row, int curr_col, char player, int check_range);

#endif
