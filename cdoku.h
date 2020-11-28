#ifndef CDOKU_H__
#define CDOKU_H__

#define BSIZE 9
#define BSIZE_D 9.0
#define BSQRTSIZE 3

#define cell_n(i, j) ((i/BSQRTSIZE)*BSQRTSIZE + j/BSQRTSIZE)

#include <stdlib.h>

// board_t struct containing information of the resulting board
// holds row column and 9-cell lookup
typedef struct board_t 
{
    int board[BSIZE][BSIZE];
    // The outer index is the cell, column, or row number. 
    // The inner index is the number e.g. taken_row[0][8] counts number of 8s in the 0th row
    int taken_cell[BSIZE][BSIZE];
    int taken_row[BSIZE][BSIZE];
    int taken_col[BSIZE][BSIZE];
} board;

board generate_board(void);
char is_conflict(board *b, int r, int c);
void print_board(board *b); 
void remove_cells(board *b, int n);
#endif
