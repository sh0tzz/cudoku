#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void loadGrid(int *p_array)
{
	FILE *f_ptr = fopen("grid.txt", "r");
	if (f_ptr == NULL) {
		printf("File grid.txt not found\n");
		exit(EXIT_FAILURE);
	}
	char ch;
	int i = 0;
	while ((ch = fgetc(f_ptr)) != EOF) {
		if (i > 81) {
			printf("Too many numbers in 'grid.txt'\n");
			exit(EXIT_FAILURE);
		}
		if (ch >= '0' && ch <= '9') {
			*(p_array + i) = ch - '0';
			i++;
		}
	}
	if (i < 81) {
		printf("Not enough numbers in 'grid.txt'\n");
		exit(EXIT_FAILURE);
	}
	fclose(f_ptr);
}

void renderGrid(int *p_grid)
{
	int i, j;
	printf("┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓\n");
	for (i = 0; i < 9; i++) {
		printf("┃");
		for (j = 0; j < 9; j++) {
			printf(" %d ", *(p_grid+i*9+j));
			if ((j+1) % 3 == 0) {
				printf("┃");
			}
		}
		printf("\n");
		if ((i+1) % 3 == 0 && i != 8) {
			printf("┣━━━━━━━━━╋━━━━━━━━━╋━━━━━━━━━┫\n");
		}
	}
   	printf("┗━━━━━━━━━┻━━━━━━━━━┻━━━━━━━━━┛\n");	
}

bool isPossible(int x, int y, int num, int *p_grid)
{
	int i;
	for (i = 0; i < 9; i++) {
		if (*(p_grid + y*9 + i) == num) {
			return false;
		}
		if (*(p_grid + i*9 + x) == num) {
			return false;
		}
	}
	int square_x = x / 3 * 3;
	int square_y = y / 3 * 3;
	int j;
	for (i = square_y; i < square_y + 3; i++) {
		for (j = square_x; j < square_y + 3; j++) {
			if (*(p_grid + i*9 + j)	== num) {
				return false;
			}
		}
	}
	return true;
}

void fillFreeSpots(int *p_grid)
{
	int i, j, k;
	int possibles[9], index;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (*(p_grid + i*9 + j) == 0) {
				memset(&possibles, 0, sizeof(possibles));
				index = 0;
				for (k = 1; k <= 9; k++) {
					if (isPossible(j, i, k, p_grid)) {
						possibles[index] = k;
						index++;
					}
				}
				if (index == 1) {
					*(p_grid + i*9 + j) = possibles[0];
					printf("Set (%d,%d) to %d\n", j, i, possibles[0]);
				}
			}
		}
	}
}

int main()
{
	int grid[9][9];
	int *p_grid = &grid[0][0];
	loadGrid(p_grid);
	while (true) {
		fillFreeSpots(p_grid);
		break;
	}
	renderGrid(p_grid);
	return 0;
}
