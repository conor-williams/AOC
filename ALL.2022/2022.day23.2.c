#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>

#include <unistd.h>

FILE *a;
#define LINE 100 
#define getchar()
int var_round;
int fd;
void sigfunc(int a) {
	fflush(stdout); dup2(fd, 1); 
	printf("var_round: [[ %d ]]\n", var_round);
	fflush(stdout); fd = dup(1); close(1);
}

#define SX 8000
char grid[SX][SX];
//char gridTmp[SX][SX];
int gridTmp[SX][SX];
char gridNew[SX][SX];

#define PAD 4800
void prinit();

int leny = PAD;
int lenx = 0;

void printit();

void moveNfirst();
void moveSfirst();
void moveEfirst();
void moveWfirst();
void setitup(int reset);
int MaxX, MinX, MaxY, MinY;
void getMaxes();
char line33[6000];
int main(int argc, char **argv)
{
	signal(SIGQUIT, &sigfunc);
	// printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day 23.2\n"); fflush(stdout);
	//printf("SLOW ~4.5jegyzőkönyv\n");
	printf("SLOW ~4.5mins\n");

	fflush(stdout); fd = dup(1); close(1);
	char line1[LINE];
	char line2[6000];
	char line3[6000];

	//int fd = dup(1); close(1);
	leny = 0;

	memset(grid, '.', sizeof(grid));
	memset(gridNew, '.', sizeof(gridNew));
	for (int i = 0; i < PAD; i++) {
		grid[i][PAD] = '\0';
		gridNew[i][PAD] = '\0';
	}
	strcpy(line33, grid[0]);
	//printf("%s\n", grid[0]);
	int sx = (PAD/2); int sy = (PAD/2);
	leny = (PAD/2);
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		for (int i = 0; i < (int)strlen(line1); i++) {
			grid[leny][i+(PAD/2)] = line1[i];
			gridNew[leny][i+(PAD/2)] = '.';
		}
		leny++;
	}
	fclose(a);
	leny += (PAD/2);
	lenx = PAD;

	for (int i = 0; i < leny; i++) {
		grid[i][lenx] = '\0';
		gridNew[i][lenx] = '\0';
	}
	printf("lenx is %d leny is %d\n", lenx, leny);
	getchar();

	int numRounds = 1700;
	if (argc == 3) {numRounds = atoi(argv[2]);}
	int rounds = 0;
	setitup(0);
	
	do {
		getMaxes();
		{
			//fflush(stdout); dup2(fd, 1); 
			//printit();
			printf("var_round: %d --- %d %d %d %d\n", var_round, MinX, MaxX, MinY, MaxY);
			//fflush(stdout); fd = dup(1); close(1);
			getchar();
		}
		
		//===============
		//if (rounds == 0) {setitup(0);} else {setitup(1);}

		moveNfirst();
		printf("moved N first\n");
		var_round = rounds;
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds); getchar();
		//printit(); getchar();
		if (rounds == numRounds) {break;}
		//====================
		moveSfirst();
		printf("moved S first\n");
		var_round = rounds;
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds);
		//printit(); getchar();
		if (rounds == numRounds) {break;}
		//=====================
		moveWfirst();
		printf("moved W first\n");
		var_round = rounds;
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds);
		//printit(); getchar();
		if (rounds == numRounds) {break;}
		//=====================
		moveEfirst();
		printf("moved E first\n");
		var_round = rounds;
		setitup(1);
		rounds++;
		printf("== End of Round %d ==\n", rounds); 
		//printit(); getchar();
		if (rounds == numRounds) {break;}
		//=====================
	} while (1);


}

void getMaxes() {
	printf("here1...\n");
	MinX = 99999;
	MinY = 99999;
	MaxX = 0;
	MaxY = 0;

	for (int y = 0; y < leny; y++) {
		for (int x = 0; x < lenx; x++) {
			if (grid[y][x] == '#') {
				printf("found hash\n");
				if (x > MaxX) {MaxX = x;}
				if (y > MaxY) {MaxY = y;}
				if (x < MinX) {MinX = x;}
				if (y < MinY) {MinY = y;}
			}			

		}
	}
}

void setitup(int reset)
{
	//printf("in setitup %d\n", reset);
	//
	//=====================
	//if (memcmp(gridNew, grid, sizeof(gridNew)) == 0) {printf("got...\n");}
	if (var_round > 2) {
		if (memcmp(gridNew, grid, sizeof(gridNew)) == 0) {fflush(stdout); dup2(fd, 1); printf("**ans: %d\n", var_round+1); exit(0);}
		/*
		int found = 0;
		for (int y = MinY-50; y < MaxY+50; y++) {
			if (strcmp(grid[y], gridNew[y]) != 0) {
				found = 1;
				break;
			}
		}
		if (found == 0) {fflush(stdout); dup2(fd, 1); printf("gotcha %d\n", var_round+1); exit(0);}
		*/
		//if (found == 0) {printf("gotcha %d\n", var_round+1); exit(0);}
	}

	memset(gridTmp, 0, sizeof(gridTmp));
	assert(gridTmp[11][21] == 0);

	if (reset == 1) {
		for (int y = MinY-50; y < MaxY+50; y++) {
			/*
			fflush(stdout); dup2(fd, 1);
			printf("%d V %d V %d\n", (int)strlen(grid[y]), (int)strlen(gridNew[y]), (int)strlen(line33));
			fd=dup(1); close(1);
			*/
			strcpy(grid[y], gridNew[y]);
			strcpy(gridNew[y], line33);
		}
	}
	//memset(gridNew, '.', sizeof(gridNew));
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
	//memset(gridNew, '.', sizeof(gridNew));
	for (int y = MinY-4; y < MaxY+4; y++) {
		for (int x = MinX-4; x < MaxX+4; x++) {
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

	for (int y = MinY-8; y < MaxY+8; y++) {
		for (int x = MinX-8; x < MaxX+8; x++) {
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
	for (int y = MinY-12; y < MaxY+12; y++) {
		for (int x = MinX-12; x < MaxX+12; x++) {
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

	for (int y = MinY-16; y < MaxY+16; y++) {
		for (int x = MinX-16; x < MaxX+16; x++) {

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
	for (int y = MinY-20; y < MaxY+20; y++) {
		for (int x = MinX-20; x < MaxX+20; x++) {
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

	for (int y = MinY-24; y < MaxY+24; y++) {
		for (int x = MinX-24; x < MaxX+24; x++) {
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
	for (int y = MinY-28; y < MaxY+28; y++) {
		for (int x = MinX-28; x < MaxX+28; x++) {
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

	for (int y = MinY-32; y < MaxY+32; y++) {
		for (int x = MinX-32; x < MaxX+32; x++) {
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
/*
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
	fflush(stdout); dup2(fd, 1);
	printf("**ans [[ %d]] \n", count);
	*/
	//if (memcmp(grid, gridNew, sizeof(grid)) == 0) {fflush(stdout); dup2(fd, 1); printit(); printf("gotcha %d\n", var_round+1);exit(0);}
	//gridTmp V grid
