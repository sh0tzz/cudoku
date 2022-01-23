#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void loadFromFile(char *filename, int *p_array)
{
	FILE *f_ptr = fopen(filename, "r");
	if (f_ptr == NULL) {
		printf("File '%s' not found\n", filename);
		exit(EXIT_FAILURE);
	}
	char ch;
	int i = 0;
	while ((ch = fgetc(f_ptr)) != EOF) {
		if (i > 81) {
			printf("Too many numbers in '%s'\n", filename);
			exit(EXIT_FAILURE);
		}
		if (ch >= '0' && ch <= '9') {
			*(p_array + i) = ch - '0';
			i++;
		}
	}
	if (i < 81) {
		printf("Not enough numbers in '%s'\n", filename);
		exit(EXIT_FAILURE);
	}
	fclose(f_ptr);
}

void loadFromString(char *string, int *p_array)
{
	int i, index=0;
	for (i = 0; i < strlen(string); i++) {
		if (index > 80) {
			printf("Too many numbers in given string\n");
			exit(EXIT_FAILURE);
		}
			printf("1: %c\n", string[i]);
		if (string[i] >= '0' && string[i] <= '9') {
			*(p_array + index) = string[i] - '0';
			index++;
		}
	}
	if (index < 81) {
		printf("Not enough numbers in given string\n");
		exit(EXIT_FAILURE);
	}
}

void renderGrid(int *p_grid)
{
	int i, j, n;
	printf("┏━━━━━━━━━┳━━━━━━━━━┳━━━━━━━━━┓\n");
	for (i = 0; i < 9; i++) {
		printf("┃");
		for (j = 0; j < 9; j++) {
			n = *(p_grid+i*9+j);
			if (n != 0) {
				printf(" %d ", n);
			} else {
				printf("   ");
			}
			
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
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (*(p_grid + square_y*9 + i*9 + square_x + j) == num) {
				return false;
			}
		}
	}
	return true;
}

int solve(int *p_grid)
{
	int i, j, k;
	int res;
	for (i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			if (*(p_grid + i*9 + j) == 0) {
				for (k = 1; k <= 9; k++) {
					if (isPossible(j, i, k, p_grid)) {
						*(p_grid + i*9 + j) = k;
						res = solve(p_grid);
						if (res == EXIT_FAILURE) {
							*(p_grid + i*9 + j) = 0;
						} else if (res == EXIT_SUCCESS) {
							return EXIT_SUCCESS;
						}
					}
				}
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	char *USAGE = "cudoku <SRC-TYPE> <SRC> [<RENDER>]\n"
				  "SRC-TYPE:\n"
				  "    -s --string    load sudoku grid from SRC string\n"
				  "    -f --file      load sudoku grid from filename provided in SRC\n"
				  "RENDER:\n"
				  "    -r -i --render-input    render unsolved grid";
	int grid[9][9];
	int *p_grid = &grid[0][0];
	if (argc >= 3 && argc <= 4) {
		if (strcmp(argv[1], "-s" ) == 0 || strcmp(argv[1], "--string") == 0) {
			loadFromString(argv[2], p_grid);
		} else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0) {
			loadFromFile(argv[2], p_grid);
		} else {
			printf("%s\n", USAGE);
		}
		if (argc == 4) {
			if (strcmp(argv[3], "-r") == 0 || strcmp(argv[3], "-i") == 0 || strcmp(argv[3],  "--render-input") == 0) {
				renderGrid(p_grid);
			} else {
				printf("%s\n", USAGE);
			}
		} 
		int result = solve(p_grid);
		if (result == EXIT_SUCCESS) {
			renderGrid(p_grid);
		} else {
			printf("Unsolvable\n");
		}
	} else {
		printf("%s\n", USAGE);
	}
	return 0;
}
