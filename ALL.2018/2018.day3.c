#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define BOARD_X 1000
#define BOARD_Y 1000
int lenx, leny;
#define DAY "		2018 day3 part1\n"
#undef _DEBUG_
//char board[1366][BOARD_X][BOARD_Y];
int board[BOARD_X][BOARD_Y];
//char (*board)[BOARD_X][BOARD_Y];
void printboard();

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[2000];

	memset(board, 0, sizeof(board));

	while(1) {
		fgets(line1, 999, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		//printf("%s\n", line1); 
		char boardnum[10]; int topleftx; int toplefty; int width; int height;
		sscanf(line1, "#%[^ ] @ %d,%d: %dx%d", boardnum, &topleftx, &toplefty, &width, &height);

		for (int x = topleftx; x < topleftx + width; x++) {
			for (int y = toplefty; y < toplefty + height; y++) {
				board[y][x]++;
			}
		}

		leny++; lenx = strlen(line1);
	}
	fclose(a);

	int count = 0;
	for (int x = 0; x < BOARD_X; x++) {
		for (int y = 0; y < BOARD_Y; y++) {
			if (board[y][x] > 1) {
				count++;
			}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", count);
}
void printboard()
{
	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			printf("%d", board[y][x]);
		}
		printf("\n");
	}
}

