#ifndef TIC_TAC_TOE_BOARD_H
#define TIC_TAC_TOE_BOARD_H

#define PLAYER_1 'X'
#define PLAYER_2 'O'

#define BOARD_ROWS 3
#define BOARD_COLS 3

/* how many tiles to check
 * the classic checks for only 3 tiles.
 */
#define BOARD_CHECK_RANGE 3 

void init_board(char board[BOARD_ROWS][BOARD_COLS]);
void draw_board(char board[BOARD_ROWS][BOARD_COLS]);
int is_board_has_space(char board[BOARD_ROWS][BOARD_COLS]);
int check_tile_position(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player);
int check_tile_position_horizontal(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player);
int check_tile_position_vertical(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player);
int check_tile_position_diagonal(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player);
int check_tile_position_diagonal_reverse(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player);

#endif
