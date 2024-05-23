#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#undef _DEBUG_
#define SIZE 40
char line1[SIZE];
long long tot = 0;
int tX, tY, depth;
struct already_s {
	int path;
	int tool;
	int both;
};

void next(int x, int y, int tool, int path, struct already_s (*al)[], char (*)[]);
#ifdef _EX1
	int minPath = 50;
#else
	int minPath = 1080;
#endif
int times;

#define WET '='
#define ROC '.'
#define NAR '|'
//////////////////
#define NEI 10
#define TOR 11
#define CLI 12

void printit(int cX, int cY, char (*)[]);

#define getchar()
int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day22.1\n"); fflush(stdout);

	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		sscanf(line1, "depth: %d", &depth);
		sscanf(line1, "target: %d,%d", &tX, &tY);
		leny++;
	}
	fclose(a);

	printf("depth::  %d\n", depth);
	printf("target:: %d :::: %d\n", tX, tY);
	fflush(stdout);

	char (*grid)[tX+351] = malloc(sizeof(char[tY+350][tX+351]));
	if (grid == NULL) {perror("gridE\n"); exit(0);}

	struct already_s (*already)[tX+351] = malloc(sizeof(struct already_s[tY+350][tX+351]));
	if (already == NULL) {perror("alreadyE\n"); exit(0);}

	long long (*geo)[tX+351] = malloc(sizeof(long long[tY+350][tX+351]));
	if (geo == NULL) {perror("geoE\n"); exit(0);}

	long long (*ero)[tX+351] = malloc(sizeof(long long[tY+350][tX+351]));
	if (ero == NULL) {perror("eroE\n"); exit(0);}

	//long long (*risk)[tX+351] = malloc(sizeof(long long[tY+350][tX+351]));
	//if (risk == NULL) {perror("riskE\n"); exit(0);}


	geo[0][0] = 0;		
	geo[tY][tX] = 0;
	
	{
		int y = 0;
		for (int x = 0; x < tX+351; x++) {
			geo[y][x] = x * 16807; 
		}

		int x = 0;
		for (int y = 0; y < tY+350; y++) {
			geo[y][x] = y * 48271;
		}
	}

	geo[0][0] = 0;		
	geo[tY][tX] = 0;
	{
		int y = 0;
		for (int x = 0; x < tX+351; x++) {
			ero[y][x] = (geo[y][x] + depth) % 20183;
		}

		int x = 0;
		for (int y = 0; y < tY+350; y++) {
			ero[y][x] = (geo[y][x] + depth) % 20183;
		}
	}
	geo[0][0] = 0;		
	geo[tY][tX] = 0;
	{
		for (int y = 1; y < tY+350; y++) {
			for (int x = 1; x< tX+351; x++) {
				if (x == 0 && y==0) {
				} else if (x == tX && y==tY) {
				} else {
					geo[y][x] = ero[y][x-1] * ero[y-1][x];
				}
				ero[y][x] = (geo[y][x] + depth) % 20183;
			}
		}
	}

	{printf("here3: ero is %lld\n", ero[0][1]);}

	{
		for (int y = 0; y < tY+350; y++) {
			for (int x = 0; x< tX+351; x++) {
				switch(ero[y][x] % 3) {
					case 0:
						grid[y][x] = ROC;
						break;
					case 1:
						grid[y][x] = WET;
						break;
					case 2:
						grid[y][x] = NAR;
						break;
				}
			}
		}
	}
	
	printf("after creating grid\n"); fflush(stdout);
	tot = 0;
	printf("**tot %lld\n", tot); getchar();

	free(geo); free(ero);

	printit(1, 1, grid);
	printf("Starting out with minPath: %d\n", minPath);
	{
		for (int y = 0; y < tY+350; y++) {
			for (int x = 0; x < tX+351; x++) {
				already[y][x].path = -1;
				already[y][x].both = 0;
			}
		}
		already[0][0].path = 0;
		already[0][0].tool = TOR;
		next(0,1, TOR, 1, already, grid);
		printf("here1");
		for (int y = 0; y < tY+350; y++) {
			for (int x = 0; x < tX+351; x++) {
				already[y][x].path = -1;
				already[y][x].both = 0;
			}
		}
		printf("here2");

		already[0][0].path = 0;
		already[0][0].tool = CLI;
		next(0,1, CLI, 8, already, grid);
////////////////////
		for (int y = 0; y < tY+350; y++) {
			for (int x = 0; x < tX+351; x++) {
				already[y][x].path = -1;
				already[y][x].both = 0;
			}
		}
		already[0][0].path = 0;
		already[0][0].tool = TOR;
		printf("here3");
		next(1,0, TOR, 1, already, grid);
		for (int y = 0; y < tY+350; y++) {
			for (int x = 0; x < tX+351; x++) {
				already[y][x].path = -1;
				already[y][x].both = 0;
			}
		}
		already[0][0].path = 0;
		already[0][0].tool = CLI;
		printf("here4");
		next(1,0, CLI, 8, already, grid);

		printf("**minPath %d\n", minPath); 
	}

	free(grid); free(already);
}

int ind = 0;
void next(int x, int y, int tool, int path, struct already_s (*already1)[tX+351], char (*gridCopy)[tX+351]) {
	ind++;

	if (x > (tX+351)-2) {return;} 
	if (x < 0) {return;}
	if (y > (tY+350)-2) {return;}
	if (y < 0) {return;}
//	printf("path is %d\n", path); printf("x,y %d,%d\n", x, y); printf("already1[y][x] %d\n", already1[y][x]);

	if (x == 0 && y == 0) {return;}

	if (x == tX && y == tY) {
		if (tool == NEI) {
			return;
		} else if (tool == TOR) {
		} else if (tool == CLI) {
			path += 7;
		} 
		if (path < minPath) {
			minPath = path;
			printf("min so far is %d\n", minPath); fflush(stdout);
		}
		return;
	}
	if (path> minPath) {return;}

	if (path< already1[y][x].path  || already1[y][x].path == -1 
		  || (already1[y][x].both == 0 && path -8 < already1[y][x].path && already1[y][x].tool != tool)) {
		int newpath;
		switch(gridCopy[y][x]) { //10 neither //11 torch //12 climbing
			case WET:
				if (tool == TOR) {return;}
				if (path<minPath || already1[y][x].path == -1) {already1[y][x].path = path; already1[y][x].both = 0; already1[y][x].tool = tool;} else
		  		if (already1[y][x].both == 0 && path -8 < already1[y][x].path && already1[y][x].tool != tool) { already1[y][x].both = 1;}
				for (int t = 10; t <= 12; t++) {
					if (t == TOR) {
						continue;
					} else {
						//already1[y][x].tool = t;
						if (t != tool) {
							newpath = path + 7+1;
						} else {
							newpath = path+1;
						}
						{next(x, y-1, t, newpath, already1, gridCopy);}
						{next(x+1, y, t, newpath, already1, gridCopy);}
						{next(x, y+1, t, newpath, already1, gridCopy);}
						{next(x-1, y, t, newpath, already1, gridCopy);}
					}
				}
				break;
			case ROC:
				if (tool == NEI) {return;}
				if (path<minPath || already1[y][x].path == -1) {already1[y][x].path = path; already1[y][x].both = 0; already1[y][x].tool = tool;} else
		  		if (already1[y][x].both == 0 && path -8 < already1[y][x].path && already1[y][x].tool != tool) { already1[y][x].both = 1;}
				for (int t = 10; t <= 12; t++) {
					if (t == NEI) {
						continue;
					} else {
						//already1[y][x].tool = t;
						if (t != tool) {
							newpath = path+ 7+1;
						} else {
							newpath = path + 1;
						}

						{next(x, y-1, t, newpath, already1, gridCopy);}
						{next(x+1, y, t, newpath, already1, gridCopy);}
						{next(x, y+1, t, newpath, already1, gridCopy);}
						{next(x-1, y, t, newpath, already1, gridCopy);}
					}
				}
				break;
			case NAR:
				if (tool == CLI) {return;}
				if (path<minPath || already1[y][x].path == -1) {already1[y][x].path = path; already1[y][x].both = 0; already1[y][x].tool = tool;} else
		  		if (already1[y][x].both == 0 && path -8 < already1[y][x].path && already1[y][x].tool != tool) { already1[y][x].both = 1;}
				for (int t = 10; t <= 12; t++) {
					if (t == CLI) {
						continue;
					} else {
						//already1[y][x].tool = t;
						if (t != tool) {
							newpath = path+ 7+1;	
						} else {
							newpath = path + 1;
						}
						{next(x, y-1, t, newpath, already1, gridCopy);}
						{next(x+1, y, t, newpath, already1, gridCopy);}
						{next(x, y+1, t, newpath, already1, gridCopy);}
						{next(x-1, y, t, newpath, already1, gridCopy);}
					}
				}
				break;
			case 'M':
				printf("ERR M\n"); exit(0);
			default:
				printf("UNK terrain %d %d [%c]\n", x, y, gridCopy[y][x]); exit(0);
		}
	}
	ind--;
}

void printit(int cX, int cY, char (*gridCopy)[tX+351]) {
	for (int y = 0; y < tY+5; y++) {
		for (int x = 0; x < tX+5; x++) {
			if (x == cX && y == cY) {
				printf("X");
			} else {
				printf("%c", gridCopy[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
	
