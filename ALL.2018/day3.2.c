#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BOARD_X 1000
#define BOARD_Y 1000
int lenx, leny;
#define DAY "2018 day3 part1\n"
#undef _DEBUG_
char board[1366][BOARD_X][BOARD_Y];
//char (*board)[BOARD_X][BOARD_Y];

void printboard(int b);

int main(int argc, char **argv)
{
//	printf("before malloc...\n");  fflush(stdout);
//	board = malloc(1366 * sizeof(char **));
//	if (board == NULL) {printf("no mem exit\n"); fflush(stdout); exit(0);}
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
        char line1[2000];

   for (int b = 0; b < 1366; b++) {
	for (int x = 0; x< BOARD_X; x++) {
		for (int y = 0 ; y < BOARD_Y; y++){
			board[b][y][x] = '.';
		}
	}
   }

int maxx = 0; int maxy = 0;
while(1) {
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	printf("%s\n", line1); 
	char boardnum[10]; int topleftx; int toplefty; int width; int height;
	printf("here2"); fflush(stdout);
	sscanf(line1, "#%[^ ] @ %d,%d: %dx%d", boardnum, &topleftx, &toplefty, &width, &height);
	printf("here2"); fflush(stdout);

	for (int x = topleftx; x < topleftx + width; x++) {
		for (int y = toplefty; y < toplefty + height; y++) {
			if (x > maxx) { maxx = x;}
			if (y > maxy) { maxy = y;}
		}
	}

	for (int x = topleftx; x < topleftx + width; x++) {
		for (int y = toplefty; y < toplefty + height; y++) {
			board[leny][y][x] = '#';
		}
	}

	//strcpy(board[leny], line1);
	leny++; lenx = strlen(line1);
	printf("lenx %d - leny %d\n", lenx, leny);
	printf("here1"); fflush(stdout);
}
	printf("maxx is %d\n", maxx);
	printf("maxy is %d getchar\n", maxy);
fclose(a);

	int foundboard[BOARD_Y][BOARD_X];
	for (int x = 0; x < BOARD_X; x++) {
		for (int y = 0; y < BOARD_Y; y++) {
			foundboard[y][x] = 0;
		}
	}
	
#ifdef _DEBUG_
	for (int i = 0; i < leny; i++) {
		printboard(i); getchar();
	}
#endif
	int foundfirst; 
	for (int x = 0; x < BOARD_X; x++) {
		for (int y = 0; y < BOARD_Y; y++) {
			foundfirst = 0; 
    			for (int i = 0; i < leny; i++) {
				//printf("x: %d y: %d\n", x, y); fflush(stdout);
				if (foundfirst == 1 && board[i][y][x] == '#') {
					//printf("found two hashes... %d,%d", x, y);
					foundboard[y][x] = 1; break;
				}
				if (foundfirst == 0 && board[i][y][x] == '#') {
					foundfirst = 1;
				}
				
   			}
			//break to here... new x and y
		}
			
	}

a = fopen(argv[1], "r"); 
while(1) {
        fgets(line1, 999, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	printf("%s\n", line1); 
	char boardnum[10]; int topleftx; int toplefty; int width; int height;
	sscanf(line1, "#%[^ ] @ %d,%d: %dx%d", boardnum, &topleftx, &toplefty, &width, &height);

	int found22 = 0;
	for (int x = topleftx; x < topleftx + width; x++) {
		for (int y = toplefty; y < toplefty + height; y++) {
			if (foundboard[y][x] == 0) {
			} else {
				found22 = 1; goto after;
			}
		}
	}
after:
	if (found22 == 0) {
		printf("***%s\n", boardnum); getchar(); getchar();
	}
}
//free(board);
	int tot = 0;
	for (int x = 0; x < BOARD_X; x++) {
		for (int y = 0; y < BOARD_Y; y++) {

			if (foundboard[y][x] == 1) {tot++;}
		}
	}
	
	printf("after...\n");
	printf("\n******** tot %d\n", tot);
}
void printboard(int bnum)
{
	for (int x = 0; x < 20; x++) {
		for (int y = 0; y < 20; y++) {
			printf("%c", board[bnum][y][x]);
		}
		printf("\n");
	}
}

