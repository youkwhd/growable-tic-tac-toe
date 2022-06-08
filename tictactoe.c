#include <stdio.h>
#include "board.h"

#define PLAYER_1 'X'
#define PLAYER_2 'O'

/* gets player y x input, player is relative to `player_turn`
 * then append the input into desired input tile
 */
void get_player_input_and_mark_tile(char board[BOARD_ROWS][BOARD_COLS]) {
    /* who's turn not how many turns.
     */
    static int player_turn = 1; 
    int row, col;

    printf("player %d's turn\ninput: ", player_turn);
    scanf("%d %d", &row, &col);

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
    if (board[row][col] != ' ' || row >= BOARD_ROWS || col >= BOARD_COLS) {
        return;
    }

    switch (player_turn) {
        case 1:
            board[row][col] = PLAYER_1;
            player_turn++;
            break;
        case 2:
            board[row][col] = PLAYER_2;
            /* reset to the first player in order to cycle
             *
             * NOTE: if you want to add more player, increment `player_turn`
             * append the same `player_turn = 1` to the last player so it can cycle.
             */
            player_turn = 1;
            break;
    }
}

/* checks if a player has 
 * found a solution (has won)
 */
int check_game_winner(char board[BOARD_ROWS][BOARD_COLS]) {
    int player_has_won = 0;

    for (int i = 0; i < BOARD_ROWS; i++) { 
        for (int j = 0; j < BOARD_COLS; j++) {
            /* using `switch` just because i need to
             * correct which player won.
             */
            switch (board[i][j]) {
                case PLAYER_1:
                    player_has_won = check_tile_position(board, i, j, board[i][j]);
                    if (player_has_won) {
                        return 1;
                    }

                    break;
                case PLAYER_2:
                    player_has_won = check_tile_position(board, i, j, board[i][j]);
                    if (player_has_won) {
                        return 2;
                    }

                    break;
            }
        }
    }

    return 0;
}

int main(int argc, char **argv) {
    char board[BOARD_ROWS][BOARD_COLS];

    init_board(board);
    draw_board(board);
    printf("\n");

    while (1) {
        if (!is_board_has_space(board)) {
            printf("no one wins!\n");
            break;
        }

        get_player_input_and_mark_tile(board);
        draw_board(board);
        printf("\n");

        int player_winner_num = check_game_winner(board);
        if (player_winner_num) {
            printf("player %d won!\n", player_winner_num);
            break;
        }
    }

    return 0;
}
