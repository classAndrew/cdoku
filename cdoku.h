#ifndef CDOKU_H__
#define CDOKU_H__
#define BSIZE 9
#define BSQRTSIZE 3
#include <stdlib.h>

// board_t struct containing information of the resulting board
// holds row column and 9-cell lookup
typedef struct board_t 
{
    int board[BSIZE][BSIZE];
    char taken_cell[BSIZE][BSIZE];
    char taken_row[BSIZE][BSIZE];
    char taken_col[BSIZE][BSIZE];
} board;

board generate_board(void);
char is_conflict(board *b, int r, int c);
void print_board(board *b); 
#endif
