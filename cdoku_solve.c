#include "cdoku_solve.h"

/*
 * This is an algorithm designed to solve a sudoku puzzle. The algorithm
 * is a simple backtracking method by trying all possible numbers per
 * cell in order. 
 *
 * After choosing a number, the algorithm will make the assumption and
 * try another empty slot in the same row. If all the slots in the row
 * are filled, then move on to the next row.
 *
 * Once a call encounters no possible numbers to choose from, then
 * return and try another number in a slot previous to it
 *
 * If all possible cells are filled, then we have a solution :) 
 */

// Empty is number of empty slots
// Returns true if solved
char solve(board *b, int empty)
{
    if (empty <= 0) return 1;

    for (int i = 0; i < BSIZE; i++) 
    {
        for (int j = 0; j < BSIZE; j++)
        {
            if (b->board[i][j] == -1) 
            {
                int possible = 0;  
                // Find possible numbers
                // printf("At %d, %d: ", i, j);
                // for (int n = 0; n < BSIZE; n++) if ( 
                //     !b->taken_cell[cell_n(i, j)][n] && !b->taken_row[i][n] && !b->taken_col[j][n]) printf("%d ", n);
                // putchar('\n');
                for (int n = 0; n < BSIZE; n++) 
                {
                    char try = !b->taken_cell[cell_n(i, j)][n] && 
                        !b->taken_row[i][n] && !b->taken_col[j][n];
                    possible += try;
                    if (try) 
                    {
                        b->board[i][j] = n;
                        b->taken_cell[cell_n(i, j)][n]++;
                        b->taken_row[i][n]++;
                        b->taken_col[j][n]++;
                        char result = solve(b, empty-1);
                        if (result)
                        {
                            return 1; 
                        }
                        b->board[i][j] = -1;
                        b->taken_cell[cell_n(i, j)][n]--;
                        b->taken_row[i][n]--;
                        b->taken_col[j][n]--;
                        // You need subt possiblities to prevent a cycle
                        possible--;
                    } 
                } 
                if (!possible) return 0;
            }  
        } 
    }
    return 0;
}
 
