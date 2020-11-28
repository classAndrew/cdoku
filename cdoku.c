#include <stdio.h>
#include "cdoku.h"

int main() 
{
    board b = generate_board();
    remove_cells(&b, 3);    
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
            int cell_num = (i/BSQRTSIZE)*BSQRTSIZE+(offset/BSQRTSIZE); 
            b.taken_cell[cell_num][j] = 1; 
        }
    } 
    
    return b;
}

// Remove n individual cells randomly
// -1 marks an empty cell
void remove_cells(board *b, int n) 
{
    char removing[BSIZE][BSIZE] = {};
    
    while (n) 
    {
        int i = random()*BSIZE_D/RAND_MAX;
        int j = random()*BSIZE_D/RAND_MAX;
        // if we have already removed it, try again. 
        if (removing[i][j]) continue;
        removing[i][j] = 1;
        // empty the cell and update counter values
        int digit = b->board[i][j]; 
        b->taken_row[i][digit]--;
        b->taken_col[j][digit]--;
        b->taken_cell[cell_n(i, j)][digit]--; 
        b->board[i][j] = -1;
        n--;
    }
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
    for (int l = 0; l < BSQRTSIZE; l++)
    {
        for (int i = l*BSQRTSIZE; i < BSQRTSIZE*(l+1); i++)
        {
            for (int k = 0; k < BSQRTSIZE; k++) 
            {
                for (int j = k*BSQRTSIZE; j < (k+1)*BSQRTSIZE; j++) 
                {
                    b->board[i][j] == -1 ? printf(" ") : printf("%d", b->board[i][j]);
                    if (j < (k+1)*BSQRTSIZE-1) putchar(' '); 
                }
                if (k < BSQRTSIZE-1) putchar('|'); 
            }
            putchar('\n');
        } 

        if (l < BSQRTSIZE-1) 
        {
            for (int j = 0; j < BSQRTSIZE; j++) 
            {
                for (int i = 0; i < BSQRTSIZE*2-1; i++)
                {
                    putchar('-');         
                }
                if (j < BSQRTSIZE-1) putchar('+');
            }
            putchar('\n');
        }
    } 
}
