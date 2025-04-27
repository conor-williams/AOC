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
#define DAY "		2018 Day3 part2\n"
#undef _DEBUG_
int board[BOARD_X][BOARD_Y];
int boardClaim[BOARD_X][BOARD_Y];
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
		char boardnum[10]; int topleftx; int toplefty; int width; int height;
		sscanf(line1, "#%[^ ] @ %d,%d: %dx%d", boardnum, &topleftx, &toplefty, &width, &height);

		for (int x = topleftx; x < topleftx + width; x++) {
			for (int y = toplefty; y < toplefty + height; y++) {
				board[y][x]++;
				boardClaim[y][x] = atoi(boardnum);
			}
		}

		leny++; lenx = strlen(line1);
	}
	fclose(a);

	a = fopen(argv[1], "r"); 
	int bNum = 0;
	while(1) {
		fgets(line1, 999, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		char boardnum[10]; int topleftx; int toplefty; int width; int height;
		sscanf(line1, "#%[^ ] @ %d,%d: %dx%d", boardnum, &topleftx, &toplefty, &width, &height);

		int found = 0;
		for (int x = topleftx; x < topleftx + width; x++) {
			for (int y = toplefty; y < toplefty + height; y++) {
				if (board[y][x] == 1) {}
				else {found = 1;}
			}
		}
		if (found == 0) {bNum = atoi(boardnum); printf("%d unoverlap\n", bNum);}

	}
	fclose(a);


	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", bNum);
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

