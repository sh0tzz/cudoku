#include <stdio.h>

void renderGrid(int *p_grid) {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			printf(" %d ", *(p_grid+i*9+j));
			if (i+1 % 3 == 0) {
				printf("|");
			}
		}
		printf("\n");
	}	
}

int main()
{
	int i, j;
	int grid[9][9];
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			grid[i][j] = 0;
		}
	}
	renderGrid(&grid[0][0]);
	return 0;
}
