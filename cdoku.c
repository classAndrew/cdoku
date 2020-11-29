#include "cdoku_gen.h"
#include "cdoku_solve.h"

int main() 
{
    board b = generate_board();
    remove_cells(&b, 80); 
    char res = solve(&b, 80);
    printf("Solved: %d\n", res);
    print_board(&b);
}

