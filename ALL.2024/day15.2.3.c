#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>

using namespace std;
FILE *a;
#define LINE 2000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

char grid[300][300];
char gridTmp[300][300];
char moves[21000];
void printit();
int sx, sy;
int checkAbove(int fir, int sec, int y);
int checkBelow(int fir, int sec, int y);
void makeMoveUp();
void makeMoveDown();
vector <pair<int, int>> ve;
void makeMove();
int madeMove = 1;

int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 15 Part 1\n"); fflush(stdout);
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
	memset(gridTmp, '\0', sizeof(gridTmp));
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			switch (grid[y][x]) {
				case '.':
					gridTmp[y][x*2] = '.';
					gridTmp[y][x*2+1] = '.';
					break;
				case '#':
					gridTmp[y][x*2] = '#';
					gridTmp[y][x*2+1] = '#';
					break;
				case 'O':
					gridTmp[y][x*2] = '[';
					gridTmp[y][x*2+1] = ']';
					break;
				case '@':
					gridTmp[y][x*2] = '@';
					gridTmp[y][x*2+1] = '.';
					break;
			}
		}
	}
	lenx *= 2;
	for (int y = 0; y < leny; y++) {
		strcpy(grid[y], gridTmp[y]);
	}

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
	printit(); getchar();

	int numMoves = (int)strlen(moves);
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			gridTmp[y][x] = grid[y][x];
		}
	}
	for (int i = 0; i < numMoves; i++) {
		if (!ve.empty()) {ve.clear();}
		if (madeMove == 1) {
			for (int y = 0; y < leny; y++) {
				for (int x = 0; x < lenx; x++) {
					gridTmp[y][x] = grid[y][x];
				}
			}
		}
		madeMove = 0;

		switch (moves[i]) {
			case '^':
				//sx stays same
				if (grid[sy-1][sx] == '.' && grid[sy-1][sx+1] == '.') {
					sy--;
					goto nextMove;
				} else if (grid[sy-1][sx] == '#' || grid[sy-1][sx+1] == '#') {
					//no move
					goto nextMove;
				} else if (grid[sy-1][sx] == '.' && grid[sy-1][sx+1] == '[') {
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret = checkAbove(sx+1, sx+2, sy-1);
					if (ret == -1) {
						goto nextMove;
					} else {
						makeMoveUp();
						sy--;
					}
				} else if (grid[sy-1][sx] == '[' && grid[sy-1][sx+1] == ']') {
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret = checkAbove(sx, sx+1, sy-1);
					if (ret == -1) {
						goto nextMove;
					} else {
						makeMoveUp();
						sy--;
					}
					
				} else if (grid[sy-1][sx] == ']' && grid[sy-1][sx+1] == '.') {
					printf("up here1 (].)\n");
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret = checkAbove(sx, sx-1, sy-1);
					if (ret == -1) {
						goto nextMove;
					} else {
						makeMoveUp();
						sy--;
					}
				} else if (grid[sy-1][sx] == ']' && grid[sy-1][sx+1] == '[') {
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret1 = checkAbove(sx, sx-1, sy-1);
					if (ret1 == -1) {
						goto nextMove;
					} else {
						int ret2 = checkAbove(sx+1, sx+2, sy-1);
						if (ret2 == -1) {
							goto nextMove;
						} else {
							makeMoveUp();
							sy--;
						}
					}
				} else {
					printit();
					printf("ERR^"); exit(0);
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
				} else if (grid[sy][sx+1] == '[') {
					//O with no dot ending in hash -- no move
					for (int x = sx+2; x < lenx; x++) {
						if (grid[sy][x] == '.') {
							grid[sy][sx+1] = '.';
							grid[sy][x] = '[';
							for (int x1 = sx+2; x1 <= x; x1++) {
								if (grid[sy][x1] == '[') {
									grid[sy][x1] = ']';
								} else if (grid[sy][x1] == ']') {
									grid[sy][x1] = '[';
								} else {
									printf("ERR>["); exit(0);
								}
							}
							sx++;
							goto nextMove;
						} else if (grid[sy][x] == '[' || grid[sy][x] == ']') {
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
				if (grid[sy+1][sx] == '.' && grid[sy+1][sx+1] == '.') {
					sy++;
					goto nextMove;
				} else if (grid[sy+1][sx] == '#' || grid[sy+1][sx+1] == '#') {
					//no move
					goto nextMove;
				} else if (grid[sy+1][sx] == '.' && grid[sy+1][sx+1] == '[') {
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret = checkBelow(sx+1, sx+2, sy+1);
					if (ret == -1) {
						goto nextMove;
					} else {
						makeMoveDown();
						sy++;
					}
				} else if (grid[sy+1][sx] == '[' && grid[sy+1][sx+1] == ']') {
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret = checkBelow(sx, sx+1, sy+1);
					if (ret == -1) {
						goto nextMove;
					} else {
						makeMoveDown();
						sy++;
					}
					
				} else if (grid[sy+1][sx] == ']' && grid[sy+1][sx+1] == '.') {
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret = checkBelow(sx, sx-1, sy+1);
					if (ret == -1) {
						goto nextMove;
					} else {
						makeMoveDown();
						sy++;
					}
				} else if (grid[sy+1][sx] == ']' && grid[sy+1][sx+1] == '[') {
					pair pa1 = make_pair(sx, sy); ve.push_back(pa1);
					int ret1 = checkBelow(sx, sx-1, sy+1);
					if (ret1 == -1) {
						goto nextMove;
					} else {
						int ret2 = checkBelow(sx+1, sx+2, sy+1);
						if (ret2 == -1) {
							goto nextMove;
						} else {
							makeMoveDown();
							sy++;
						}
					}
				} else {
					printit();
					printf("ERRv"); exit(0);
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
				} else if (grid[sy][sx-1] == ']') {
					//O with no dot ending in hash -- no move
					for (int x = sx-2; x > 0; x--) {
						if (grid[sy][x] == '.') {
							grid[sy][sx-1] = '.';
							grid[sy][x] = ']';
							for (int x1 = sx-2; x1 >= x; x1--) {
								if (grid[sy][x1] == '[') {
									grid[sy][x1] = ']';
								} else if (grid[sy][x1] == ']') {
									grid[sy][x1] = '[';
								} else {
									printf("ERR<["); exit(0);
								}
							}
							sx--;
							goto nextMove;
						} else if (grid[sy][x] == '[' || grid[sy][x] == ']') {
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
		if (madeMove == 1) {
			for (int y = 0; y < leny; y++) {
				for (int x = 0; x < lenx; x++) {
					grid[y][x] = gridTmp[y][x];
				}
			}
		}
		printit(); printf("MOVE: %c\n", moves[i]); getchar();
		continue;
	}
	unsigned long long ans = 0;
	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '[') {
				ans += (100 * y) + x;
			}
		}
	}
	printf("**ans %llu\n", ans);
}
void makeMoveUp() {
	if (madeMove == 0) {madeMove = 1;}
	printf("x,y: ");
	for (auto it = ve.begin(); it != ve.end(); it++) {
		pair pa = *it;
		printf("%d,%d -- ", pa.first, pa.second);
		//char from1 = grid[pa.first][pa.second]; 
		//char to1   = grid[pa.first-1][pa.second];
		gridTmp[pa.second-1][pa.first] = grid[pa.second][pa.first];
	}
	if (grid
	printf("\n");
}
		
void makeMoveDown() {
	if (madeMove == 0) {madeMove = 1;}
	for (auto it = ve.begin(); it != ve.end(); it++) {
		pair pa = *it;
		gridTmp[pa.second+1][pa.first] = grid[pa.second][pa.first];
	}
}
		

int checkBelow(int fir, int sec, int y) {
	if (y > leny-1) {return -1;}

	if (grid[y+1][fir] == '.') {
		pair tmp = make_pair(fir, y);
		ve.push_back(tmp);
		//ok
	} else if (grid[y+1][fir] == '#') {	
		return -1;	
	} else if (grid[y+1][fir] == '[') {
		int ret1 = checkBelow(fir, fir+1, y+1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(fir, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(fir+1, y);
			ve.push_back(tmp2);
		}
	
	} else if (grid[y+1][fir] == ']') {
		int ret1 = checkBelow(fir, fir-1, y+1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(fir, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(fir-1, y);
			ve.push_back(tmp2);
		}
	}

	if (grid[y+1][sec] == '.') {
		pair tmp = make_pair(sec, y);
		ve.push_back(tmp);
		//ok
	} else if (grid[y+1][sec] == '#') {	
		return -1;	
	} else if (grid[y+1][sec] == '[') {
		int ret1 = checkBelow(sec, sec+1, y+1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(sec, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(sec+1, y);
			ve.push_back(tmp2);
		}
	
	} else if (grid[y+1][sec] == ']') {
		int ret1 = checkBelow(sec, sec-1, y+1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(sec, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(sec-1, y);
			ve.push_back(tmp2);
		}
	}
	return 0;
}

int checkAbove(int fir, int sec, int y) {
	if (y < 0) {return -1;}

	if (grid[y-1][fir] == '.') {
		pair tmp = make_pair(fir, y);
		ve.push_back(tmp);
		//ok
	} else if (grid[y-1][fir] == '#') {	
		return -1;	
	} else if (grid[y-1][fir] == '[') {
		printf("in checkAbove fir [\n");
		int ret1 = checkAbove(fir, fir+1, y-1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(fir, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(fir+1, y);
			ve.push_back(tmp2);
		}
	
	} else if (grid[y-1][fir] == ']') {
		int ret1 = checkAbove(fir, fir-1, y-1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(fir, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(fir-1, y);
			ve.push_back(tmp2);
		}
	}

	if (grid[y-1][sec] == '.') {
		printf("in checkAbove sec dot\n");
		pair tmp = make_pair(sec, y);
		ve.push_back(tmp);
		//ok
	} else if (grid[y-1][sec] == '#') {	
		return -1;	
	} else if (grid[y-1][sec] == '[') {
		int ret1 = checkAbove(sec, sec+1, y-1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(sec, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(sec+1, y);
			ve.push_back(tmp2);
		}
	
	} else if (grid[y-1][sec] == ']') {
		int ret1 = checkAbove(sec, sec-1, y-1);
		if (ret1 == -1) {
			return -1;
		} else {
			pair tmp1 = make_pair(sec, y);
			ve.push_back(tmp1);
			pair tmp2 = make_pair(sec-1, y);
			ve.push_back(tmp2);
		}
	}
	return 0;
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
