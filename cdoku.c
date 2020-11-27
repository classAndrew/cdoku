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
    
    // 0-Initialize everything
    for (int i = 0; i < BSIZE; i++) 
    {
        for (int j = 0; j < BSIZE; j++) 
        {
            b.taken_row[i][j] = 0;
            b.taken_col[i][j] = 0;
            b.taken_cell[i][j] = 0; 
            b.board[i][j] = 0;
        }
    } 
    // Begin filling board values while checking for collision 
    for (int i = 0; i < BSIZE; i++) 
    {
        for (int j = 0; j < BSIZE; j++) 
        {
            // A better random algorithm would be to 'choose out of a bag'
            // However, such algorithm will run in O(BSIZE^2) per cell.
            int rand = random()*9.0/RAND_MAX + 1;
            board *board_p = &b;
            b.board[i][j] = rand; 
            while (is_conflict(board_p, i, j)) 
            {
                rand = random()*9.0/RAND_MAX+1;
                b.board[i][j] = rand; 
            }       
            b.taken_row[i][rand] = 1;
            b.taken_col[j][rand] = 1;
            int cell_n = (i/BSQRTSIZE)*BSQRTSIZE+(j/BSQRTSIZE); 
            b.taken_cell[cell_n][rand] = 1;
            print_board(board_p);
            putchar('\n'); 
        }
    }

    return b;
}

// Check if there is the same number in the row, column, or 9-cell
char is_conflict(board *b, int r, int c) 
{
    int n = b->board[r][c];
    int cell_n = (r/BSQRTSIZE)*BSQRTSIZE+(c/BSQRTSIZE); 
    
    char same_incell = b->taken_cell[cell_n][n];
    char same_inrow = b->taken_row[r][n];
    char same_incol = b->taken_col[c][n];
    
    return same_incell || same_inrow || same_incol;
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
