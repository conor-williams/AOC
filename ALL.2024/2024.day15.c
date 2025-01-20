#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
FILE *a;
#define LINE 2000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

char grid[100][100];
char moves[21000];
void printit();
int sx, sy;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 15 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	leny = 0;
	strcpy(moves, "");
	int numLines = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        //printf("LINE: %s\n", line1);
	if (line1[0] == '\0') {
		numLines = leny;
		continue;
	} else if (line1[0] == '#') {
		strcpy(grid[leny], line1);
	} else if (line1[0] == '^' || line1[0] == '>' || line1[0] == 'v' || line1[0] == '<') {
		strcat(moves, line1);
	}
		
	leny++;
}
fclose(a);
	
	leny = numLines;
	lenx =  (int)strlen(grid[0]);
	printf("move len is %d\n", (int)strlen(moves));
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '@') {
				grid[y][x] = '.';
				sx = x; sy = y; goto after;
			}
		}
	}
after:

	int numMoves = (int)strlen(moves);
	for (int i = 0; i < numMoves; i++) {
		//printit(); printf("MOVE: %c\n", moves[i]); getchar();
		switch (moves[i]) {
			case '^':
				//sx stays same
				if (grid[sy-1][sx] == '.') {
					sy--;
					goto nextMove;
				} else if (grid[sy-1][sx] == '#') {
					//no move
					goto nextMove;
				} else if (grid[sy-1][sx] == 'O') {
					//O with no dot ending in hash -- no move
					for (int y = sy-2; y > 0; y--) {
						if (grid[y][sx] == '.') {
							grid[sy-1][sx] = '.';
							grid[y][sx] = 'O';
							sy--;
							goto nextMove;
						} else if (grid[y][sx] == 'O') {
							continue;
							//keep going until space
						} else if (grid[y][sx] == '#') {
							//nomove
							goto nextMove;
						} else {
							printf("ERR^"); exit(0);
						}
					}
				}
				break;
			case '>':
				//y stays same
				if (grid[sy][sx+1] == '.') {
					sx++;
					goto nextMove;
				} else if (grid[sy][sx+1] == '#') {
					//no move
					goto nextMove;
				} else if (grid[sy][sx+1] == 'O') {
					//O with no dot ending in hash -- no move
					for (int x = sx+2; x < lenx; x++) {
						if (grid[sy][x] == '.') {
							grid[sy][sx+1] = '.';
							grid[sy][x] = 'O';
							sx++;
							goto nextMove;
						} else if (grid[sy][x] == 'O') {
							continue;
							//keep going until space
						} else if (grid[sy][x] == '#') {
							//nomove
							goto nextMove;
						} else {
							printf("ERR>"); exit(0);
						}
					}
				}
				break;
			case 'v':
				//sx stays same
				if (grid[sy+1][sx] == '.') {
					sy++;
					goto nextMove;
				} else if (grid[sy+1][sx] == '#') {
					//no move
					goto nextMove;
				} else if (grid[sy+1][sx] == 'O') {
					//O with no dot ending in hash -- no move
					for (int y = sy+2; y < leny; y++) {
						if (grid[y][sx] == '.') {
							grid[sy+1][sx] = '.';
							grid[y][sx] = 'O';
							sy++;
							goto nextMove;
						} else if (grid[y][sx] == 'O') {
							continue;
							//keep going until space
						} else if (grid[y][sx] == '#') {
							//nomove
							goto nextMove;
						} else {
							printf("ERRv"); exit(0);
						}
					}
				}
				break;
			case '<':
				//sy stays same
				if (grid[sy][sx-1] == '.') {
					sx--;
					goto nextMove;
				} else if (grid[sy][sx-1] == '#') {
					//no move
					goto nextMove;
				} else if (grid[sy][sx-1] == 'O') {
					//O with no dot ending in hash -- no move
					for (int x = sx-2; x > 0; x--) {
						if (grid[sy][x] == '.') {
							grid[sy][sx-1] = '.';
							grid[sy][x] = 'O';
							sx--;
							goto nextMove;
						} else if (grid[sy][x] == 'O') {
							continue;
							//keep going until space
						} else if (grid[sy][x] == '#') {
							//nomove
							goto nextMove;
						} else {
							printf("ERR<"); exit(0);
						}
					}
				}
				break;
			default:
				printf("UNK"); exit(0);
				break;
		}
nextMove:
		continue;
	}
	unsigned long long ans = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == 'O') {
				ans += (100 * y) + x;
			}
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", ans);
}

void printit() {
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (y == sy && x==sx) {
				printf("%c", '@');
			} else {
				printf("%c", grid[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
