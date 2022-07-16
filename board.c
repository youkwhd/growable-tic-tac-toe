#include <stdio.h>
#include "board.h"

/* initialize the board with spaces
 */
void init_board(char board[BOARD_ROWS][BOARD_COLS])
{
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

/* draws the board with a coordinate
 * for player to use when inserting inputs
 */
void draw_board(char board[BOARD_ROWS][BOARD_COLS])
{
    printf("\n  ");
    for (int i = 0; i < BOARD_COLS; i++) {
        printf(" [%d]", i);
    }
    printf("\n");

    for (int i = 0; i < BOARD_ROWS; i++) {
        printf("[%d]", i);
        for (int j = 0; j < BOARD_COLS; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* checks the board if it has any space left.
 * 1 for ok, 0 for none.
 */
int is_board_has_space(char board[BOARD_ROWS][BOARD_COLS])
{
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            if (board[i][j] == ' ') {
                return 1;
            }
        }
    }

    return 0;
}

/* checks for the current position passed by the program 
 * for every possible solutions.
 *
 * 1 -> found solution, 0 -> no solution found
 */
int check_tile_position(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player)
{
    int (*check_func[4])(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player) = {
        check_tile_position_horizontal,
        check_tile_position_vertical,
        check_tile_position_diagonal,
        check_tile_position_diagonal_reverse
    };

    for (int i = 0; i < 4; i++) {
        int found_solution = check_func[i](board, curr_row, curr_col, player);
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
int check_tile_position_horizontal(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player)
{
    for (int i = 0; i < BOARD_CHECK_RANGE; i++) { 
        /* checks if array selection is out-of-index, and
         * also checking if next tile is player or not
         *
         * so does for other check_tile* functions
         */
        if (curr_col + i >= BOARD_COLS ||
            board[curr_row][curr_col + i] != player) {
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
int check_tile_position_vertical(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player)
{
    for (int i = 0; i < BOARD_CHECK_RANGE; i++) { 
        if (curr_row + i >= BOARD_ROWS ||
            board[curr_row + i][curr_col] != player) {
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
int check_tile_position_diagonal(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player)
{
    for (int i = 0; i < BOARD_CHECK_RANGE; i++) { 
        if (curr_row + i >= BOARD_ROWS || curr_col + i >= BOARD_COLS ||
            board[curr_row + i][curr_col + i] != player) {
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
int check_tile_position_diagonal_reverse(char board[BOARD_ROWS][BOARD_COLS], int curr_row, int curr_col, char player)
{
    for (int i = 0; i < BOARD_CHECK_RANGE; i++) { 
        if (curr_row + i >= BOARD_ROWS || curr_col - i < 0 ||
            board[curr_row + i][curr_col - i] != player) {
            return 0;
        }
    }

    return 1;
}
