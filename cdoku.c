#include <stdio.h>
#include "cdoku.h"

int main() 
{
    board b = generate_board();
    print_board(&b);
}
/*
 * Sudoku board generation is a bit tricky. There are a couple of ways
 * to reach maximum randomization.
 * 1. You can swap any existing puzzle's columns or row in a 3x group (e.g. columns 1,2,3 -> 1,3,2)
 * 2. You can flip the puzzle over the diagonal
 * 3. You can replace the numbers: all 9's become 1's, all 1's become something else...
 * 4. Reflect it horizontally or vertically
 * 5. Transpose (rotate)
 * These 5 methods will generate 9! * 2^6 * 2 * 2 * 2 * 4 varations from one puzzle
 */

// Populate the board in sudoku-style using the shift way
board generate_board(void) 
{
    board b;
    // rotate left by constants according to row
    static const int shift[9] = {0, 3, 6, 7, 1, 4, 5, 8, 2};
    for (int i = 0; i < BSIZE; i++) 
    {
        for (int j = 0; j < BSIZE; j++) 
        {
            int offset = j-shift[i];
            // Wrap around if offset is less than 0
            offset += (offset < 0) * 9; 
            b.board[i][offset] = j;
            // Initialize everything while we're at it
            b.taken_row[i][j] = 1;
            b.taken_col[offset][j] = 1;
            // find cell number. Probably need a macro sooner or later 
            int cell_n = (i/BSQRTSIZE)*BSQRTSIZE+(offset/BSQRTSIZE); 
            b.taken_cell[cell_n][j] = 1; 
        }
    } 
    
    return b;
}

// Check if there is the same number in the row, column, or 9-cell
// This is done by counting number of some number at [r][c] if > 3
// It has to be > 3 because 3 is already the number itself in row, col, and cell
char is_conflict(board *b, int r, int c) 
{
    int n = b->board[r][c];
    int cell_n = (r/BSQRTSIZE)*BSQRTSIZE+(c/BSQRTSIZE); 
    
    int incell = b->taken_cell[cell_n][n];
    int inrow = b->taken_row[r][n];
    int incol = b->taken_col[c][n];
    return incell + inrow + incol > 3; 
}

// Just print all the numbers on the board
void print_board(board *b) 
{
    for (int i = 0; i < BSIZE; i++)
    {
        for (int j = 0; j < BSIZE; j++) 
        {
            printf("%d ", b->board[i][j]);
        }
        putchar('\n');
    } 
}
