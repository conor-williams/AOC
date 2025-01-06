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
FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

#define SX 3000

char grid[SX][SX];
//char gridTmp[SX][SX];
int gridTmp[SX][SX];
char gridNew[SX][SX];

#define PAD 100
void prinit();

int leny = PAD;
int lenx = 0;

void printit();

void moveNfirst();
void moveSfirst();
void moveEfirst();
void moveWfirst();
void setitup(int reset);
int main(int argc, char **argv)
{
	signal(SIGTSTP, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2021 Day 23.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];
	char line2[LINE];

	//int fd = dup(1); close(1);
	for (int i = 0; i < PAD; i++) {
		strcpy(grid[i], "........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................");
	}


	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);

		sprintf(line2, "%s%s%s", 
				"....................................................................................................",
				line1,
				"....................................................................................................");
		if (lenx == 0) {lenx = (int)strlen(line2);}
		strcpy(grid[leny], line2);
		leny++;
	}
	fclose(a);
	for (int i = leny; i < leny+100; i++) {
		strcpy(grid[i], "........................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................");
	}
	leny = leny+100;
	for (int i = 0; i < leny; i++) {
		grid[i][lenx] = '\0';
	}
	printit();
	getchar();

	int numRounds = 10;
	if (argc == 3) {numRounds = atoi(argv[2]);}
	int rounds = 0;
	setitup(0);
	do {
		//===============
		//if (rounds == 0) {setitup(0);} else {setitup(1);}
		moveNfirst();
		printf("moved N first\n");
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds); getchar();
		printit(); getchar();
		if (rounds == numRounds) {break;}
		//====================
		moveSfirst();
		printf("moved S first\n");
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds);
		printit(); getchar();
		if (rounds == numRounds) {break;}
		//=====================
		moveWfirst();
		printf("moved W first\n");
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds);
		printit(); getchar();
		if (rounds == numRounds) {break;}
		//=====================
		moveEfirst();
		printf("moved E first\n");
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds); 
		printit(); getchar();
		if (rounds == numRounds) {break;}
		//=====================
	} while (1);


	int minx = 99999;
	int miny = 99999;
	int maxx = 0;
	int maxy = 0;

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '#') {
				if (x > maxx) {maxx = x;}
				if (y > maxy) {maxy = y;}
				if (x < minx) {minx = x;}
				if (y < miny) {miny = y;}
			}			

		}
	}
	int count = 0;
	for (int y = miny; y <= maxy; y++) {
		for (int x = minx; x <= maxx; x++) {
			if (grid[y][x] == '.') {count++;}
		}
	}
	dup2(fd, 1);
	printf("**ans [[ %d]] \n", count);
}

void setitup(int reset)
{
	printf("in setitup %d\n", reset);
	//=====================
	memset(gridTmp, 0, sizeof(gridTmp));
	assert(gridTmp[11][21] == 0);

	if (reset == 1) {
		for (int y = 0; y < leny; y++) {
			strcpy(grid[y], gridNew[y]);
		}
	}
	memset(gridNew, '.', sizeof(gridNew));
}


void printit() {
	for (int y = 99; y < leny-99; y++) {
		for (int x = 99; x < lenx-99; x++) {
			printf("%c", grid[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

void moveNfirst()
{
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == '#' &&
					grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.' &&
					grid[y][x+1] == '.' && 
					grid[y+1][x+1] == '.' &&  grid[y+1][x] == '.' && grid[y+1][x-1] == '.' &&
					grid[y][x-1] == '.') {
				printf("all dots around\n");
				gridNew[y][x] = '#';
				continue;
				//no move of grid[y][x];
			}
			if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				gridTmp[y-1][x]++;			
				printf("Nprop\n");
				//move to grid grid[y-1][x]
			} else if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y+1][x]
				gridTmp[y+1][x]++;			
				printf("Sprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y][x-1]
				gridTmp[y][x-1]++;			
				printf("Wprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				//move to grid grid[y][x+1]
				gridTmp[y][x+1]++;
				printf("Eprop\n");
			} else if (grid[y][x] == '#') {
				printf("stays\n");
				gridNew[y][x] = '#';
			}
		}
	}

	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				if (gridTmp[y-1][x] == 1) {
					gridNew[y-1][x] = '#';
					printf("movN %d,%d\n", x, y-1);
				} else {
					printf("notmovN %d,%d\n", x, y);
					gridNew[y][x] = '#';
				}
				//move to grid grid[y-1][x]
			} else if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y+1][x] == 1) {
					gridNew[y+1][x] = '#';
					printf("movS %d,%d\n", x, y+1);
				} else {
					//move to grid grid[y+1][x]
					printf("not movS %d,%d\n", x, y);
					gridNew[y][x] = '#';			
				}
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y][x-1] == 1) {
					gridNew[y][x-1] = '#';			
					printf("movW %d,%d\n", x-1, y);
				} else {
					printf("not movW %d,%d\n", x, y);
					gridNew[y][x] = '#';			
				}
				//move to grid grid[y][x-1]
			} else if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				if (gridTmp[y][x+1] == 1) {
					gridNew[y][x+1] = '#';
					printf("movE %d,%d\n", x+1, y);
				} else {
					//move to grid grid[y][x+1]
					printf("not movE %d,%d\n", x, y);
					gridNew[y][x] = '#';
				}
			}
		}
	}
}

void moveSfirst() 
{
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == '#' &&
					grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.' &&
					grid[y][x+1] == '.' && 
					grid[y+1][x+1] == '.' &&  grid[y+1][x] == '.' && grid[y+1][x-1] == '.' &&
					grid[y][x-1] == '.') {
				gridNew[y][x] = '#';
				continue;
				//printf("all dots\n");
				//no move of grid[y][x];
			}

			if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y+1][x]
				gridTmp[y+1][x]++;			
				printf("Sprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y][x-1]
				gridTmp[y][x-1]++;			
				printf("Wprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				//move to grid grid[y][x+1]
				gridTmp[y][x+1]++;
				printf("Eprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				gridTmp[y-1][x]++;			
				printf("Nprop\n");
				//move to grid grid[y-1][x]
			} else if (grid[y][x] == '#') {
				printf("stays\n");
				gridNew[y][x] = '#';
			}
		}
	}

	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {

			if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y+1][x] == 1) {
					gridNew[y+1][x] = '#';
					printf("movS %d,%d\n", x, y+1);
				} else {
					//move to grid grid[y+1][x]
					gridNew[y][x] = '#';			
				}
				//move to grid grid[y-1][x]
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y][x-1] == 1) {
					gridNew[y][x-1] = '#';			
					printf("movW %d,%d\n", x-1, y);
				} else {
					gridNew[y][x] = '#';			
				}
				//move to grid grid[y][x-1]
			} else if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				if (gridTmp[y][x+1] == 1) {
					gridNew[y][x+1] = '#';
				} else {
					//move to grid grid[y][x+1]
					printf("movE %d,%d\n", x+1, y);
					gridNew[y][x] = '#';
				}
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				if (gridTmp[y-1][x] == 1) {
					gridNew[y-1][x] = '#';;			
					printf("movN %d,%d\n", x, y-1);
				} else {
					gridNew[y][x] = '#';
				}
			}
		}
	}
}

void moveWfirst() {
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == '#' &&
					grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.' &&
					grid[y][x+1] == '.' && 
					grid[y+1][x+1] == '.' &&  grid[y+1][x] == '.' && grid[y+1][x-1] == '.' &&
					grid[y][x-1] == '.') {
				gridNew[y][x] = '#';
				continue;
			}

			if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y][x-1]
				gridTmp[y][x-1]++;			
				printf("Wprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				//move to grid grid[y][x+1]
				gridTmp[y][x+1]++;
				printf("Eprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				gridTmp[y-1][x]++;			
				printf("Nprop\n");
				//move to grid grid[y-1][x]
			} else if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y+1][x]
				gridTmp[y+1][x]++;			
				printf("Sprop\n");
			} else if (grid[y][x] == '#') {
				printf("stays\n");
				gridNew[y][x] = '#';
			}
		}
	}

	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y][x-1] == 1) {
					gridNew[y][x-1] = '#';			
					printf("movW %d,%d\n", x-1, y);
				} else {
					gridNew[y][x] = '#';			
				}
				//move to grid grid[y][x-1]
			} else if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				if (gridTmp[y][x+1] == 1) {
					gridNew[y][x+1] = '#';
				} else {
					//move to grid grid[y][x+1]
					printf("movE %d,%d\n", x+1, y);
					gridNew[y][x] = '#';
				}
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				if (gridTmp[y-1][x] == 1) {
					gridNew[y-1][x] = '#';
					printf("movN %d,%d\n", x, y-1);
				} else {
					gridNew[y][x] = '#';
				}
			} else if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y+1][x] == 1) {
					gridNew[y+1][x] = '#';
					printf("movS %d,%d\n", x, y+1);
				} else {
					//move to grid grid[y+1][x]
					gridNew[y][x] = '#';			
				}
			}
			//move to grid grid[y-1][x]
		}
	}
}

//void moveEfirst() 
void moveEfirst() {
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == '#' &&
					grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.' &&
					grid[y][x+1] == '.' && 
					grid[y+1][x+1] == '.' &&  grid[y+1][x] == '.' && grid[y+1][x-1] == '.' &&
					grid[y][x-1] == '.') {
				gridNew[y][x] = '#';
				continue;
			}

			if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				//move to grid grid[y][x+1]
				gridTmp[y][x+1]++;
				printf("Eprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				gridTmp[y-1][x]++;			
				printf("Nprop\n");
				//move to grid grid[y-1][x]
			} else if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y+1][x]
				gridTmp[y+1][x]++;			
				printf("Sprop\n");
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				//move to grid grid[y][x-1]
				gridTmp[y][x-1]++;			
				printf("Wprop\n");
			} else if (grid[y][x] == '#') {
				printf("stays\n");
				gridNew[y][x] = '#';
			}
		}
	}

	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			if (grid[y][x] == '#' && grid[y-1][x+1] == '.' && grid[y][x+1] == '.' && grid[y+1][x+1] == '.') {
				if (gridTmp[y][x+1] == 1) {
					gridNew[y][x+1] = '#';
				} else {
					//move to grid grid[y][x+1]
					printf("movE %d,%d\n", x+1, y);
					gridNew[y][x] = '#';
				}
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y-1][x] == '.' && grid[y-1][x+1] == '.') {
				if (gridTmp[y-1][x] == 1) {
					gridNew[y-1][x] = '#';
					printf("movN %d,%d\n", x, y-1);
				} else {
					gridNew[y][x] = '#';
				}
			} else if (grid[y][x] == '#' && grid[y+1][x+1] == '.' && grid[y+1][x] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y+1][x] == 1) {
					gridNew[y+1][x] = '#';
					printf("movS %d,%d\n", x, y+1);
				} else {
					//move to grid grid[y+1][x]
					gridNew[y][x] = '#';			
				}
			} else if (grid[y][x] == '#' && grid[y-1][x-1] == '.' && grid[y][x-1] == '.' && grid[y+1][x-1] == '.') {
				if (gridTmp[y][x-1] == 1) {
					gridNew[y][x-1] = '#';			
					printf("movW %d,%d\n", x-1, y);
				} else {
					gridNew[y][x] = '#';			
				}
				//move to grid grid[y][x-1]
			}
		}
	}
}

