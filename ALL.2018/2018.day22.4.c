#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#undef _DEBUG_
#define SIZE 40
char line1[SIZE];
unsigned long long tot = 0;
int tX, tY, depth;

char (*grid1)[];

struct already_s {
	int path;
	int switch123;
};
struct already_s (*already1)[];
void next(int x, int y, int tool, int path, int switch123, struct already_s (*)[], char (*)[]);
int minPath = 1087;
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

	char (*grid)[tX+350] = malloc(sizeof(char[tY+351][tX+350]));
	if (grid == NULL) {perror("gridE\n"); exit(0);}

	unsigned long long (*geo)[tX+350] = malloc(sizeof(unsigned long long[tY+351][tX+350]));
	if (geo == NULL) {perror("geoE\n"); exit(0);}

	unsigned long long (*ero)[tX+350] = malloc(sizeof(unsigned long long[tY+351][tX+350]));
	if (ero == NULL) {perror("eroE\n"); exit(0);}

	//unsigned long long (*risk)[tX+350] = malloc(sizeof(unsigned long long[tY+351][tX+350]));
	//if (risk == NULL) {perror("riskE\n"); exit(0);}

	struct already_s (*already)[tX+350] = malloc(sizeof(struct already_s[tY+351][tX+350]));
	if (already == NULL) {perror("alreadyE\n"); exit(0);}

	geo[0][0] = 0;		
	geo[tY][tX] = 0;
	
	{
		int y = 0;
		for (int x = 0; x < tX+350; x++) {
			geo[y][x] = x * 16807; 
		}

		int x = 0;
		for (int y = 0; y < tY+351; y++) {
			geo[y][x] = y * 48271;
		}
	}

	geo[0][0] = 0;		
	geo[tY][tX] = 0;
	{
		int y = 0;
		for (int x = 0; x < tX+350; x++) {
			ero[y][x] = (geo[y][x] + depth) % 20183;
		}

		int x = 0;
		for (int y = 0; y < tY+351; y++) {
			ero[y][x] = (geo[y][x] + depth) % 20183;
		}
	}
	geo[0][0] = 0;		
	geo[tY][tX] = 0;
	{
		for (int y = 1; y < tY+351; y++) {
			for (int x = 1; x< tX+350; x++) {
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
		for (int y = 0; y < tY+351; y++) {
			for (int x = 0; x< tX+350; x++) {
				switch(ero[y][x] % 3) {
					case 0:
						grid[y][x] = ROC;
						//risk[y][x] = 0;
						break;
					case 1:
						grid[y][x] = WET;
						//risk[y][x] = 1;
						break;
					case 2:
						grid[y][x] = NAR;
						//risk[y][x] = 2;
						break;
				}
			}
		}
	}
	
	printf("after creating grid\n"); fflush(stdout);
	tot = 0;
	printf("**tot %lld\n", tot); getchar();


	already[0][0].path = 0;
	already[0][0].switch123 = 0;

	grid1 = grid;

	printit(0, 0, grid1);
	{
		for (int y = 0; y < tY+351; y++) {
			for (int x = 0; x < tX+350; x++) {
				already[y][x].path = -1;
				already[y][x].switch123 = 0;
			}
		}
	
		already[0][0].path = 0;
		already[0][0].switch123 = 0;
		already1 = already;
		grid1 = grid;
		next(0,1, TOR, 1, 0, already1, grid1);
		next(1,0, TOR, 1, 0, already1, grid1);

		printf("**minPath %d\n", minPath); 
	}



//	free(grid); free(geo); free(ero); free(risk); free(already);
//	free(*grid); free(*geo); free(*ero); free(*risk); free(*already);
}

void printit(int cX, int cY, char (*grid1)[tX+350]) {
	for (int y = 0; y < tY+5; y++) {
		for (int x = 0; x < tX+5; x++) {
			if (x == cX && y == cY) {
				printf("X");
			} else {
				printf("%c", grid1[y][x]);
			}
		}
		printf("\n");
	}
	printf("\n");
}
	
int ind = 0;
void next(int x, int y, int tool, int path, int switch123, struct already_s (*already1)[tX+350], char (*grid1)[tX+350]) {
	ind++;
	if (x > (tX+350)-2) {return;}
	if (x < 0) {return;}
	if (y > (tY+351)-2) {return;}
	if (y < 0) {return;}

	if (x == 0 && y == 0) {return;}

	if (x == tX && y == tY) {
		if (tool == 10) {
			return;
		} else if (tool == 11) {
		} else if (tool == 12) {
			//path += 7;
			switch123++;
		} 
		if (path +(switch123*7)< minPath) {
			printf("min so far is %d switch123: %d tot: %d\n", minPath, switch123, path+(switch123*7));
			minPath=path+(switch123*7);
		}
		return;
	}
	if (path > minPath) {return;}

	if (already1[y][x].path == -1 || (path < (already1[y][x].path + (7*switch123) ) ) ) {
		int newpath; int newSwitch = 0;
		switch(grid1[y][x]) { //10 neither //11 torch //12 climbing
			case WET:
				if (tool == TOR) {return;}
				{already1[y][x].path = path; already1[y][x].switch123 = switch123;}
				for (int t = 10; t <= 12; t++) {
					if (t == TOR) {
						continue;
					} else {
						if (t != tool) {
							newpath = path+ 1;
							newSwitch = switch123+1;
							
						} else {
							newpath = path + 1;
						}
						{next(x, y-1, t, newpath, newSwitch, already1, grid1);}
						{next(x+1, y, t, newpath, newSwitch, already1, grid1);}
						{next(x, y+1, t, newpath, newSwitch, already1, grid1);}
						{next(x-1, y, t, newpath, newSwitch, already1, grid1);}
					}
				}
				break;
			case ROC:
				if (tool == NEI) {return;}
				{already1[y][x].path = path; already1[y][x].switch123 = newSwitch;}
				for (int t = 10; t <= 12; t++) {
					if (t == NEI) {
						continue;
					} else {
						if (t != tool) {
							newpath = path +1;
							newSwitch = switch123+1;
						} else {
							newpath = path + 1;
						}

						{next(x, y-1, t, newpath, newSwitch, already1, grid1);}
						{next(x+1, y, t, newpath, newSwitch, already1, grid1);}
						{next(x, y+1, t, newpath, newSwitch, already1, grid1);}
						{next(x-1, y, t, newpath, newSwitch, already1, grid1);}
					}
				}
				break;
			case NAR:
				if (tool == CLI) {return;}
				{already1[y][x].path = path; already1[y][x].switch123 = newSwitch;}
				for (int t = 10; t <= 12; t++) {
					if (t == CLI) {
						continue;
					} else {
						if (t != tool) {
							newpath = path + 1;	
							newSwitch = newSwitch+1;
						} else {
							newpath = path + 1;
						}
						{next(x, y-1, t, newpath, newSwitch, already1, grid1);}
						{next(x+1, y, t, newpath, newSwitch, already1, grid1);}
						{next(x, y+1, t, newpath, newSwitch, already1, grid1);}
						{next(x-1, y, t, newpath, newSwitch, already1, grid1);}
					}
				}
				break;
			case 'M':
				printf("ERR M\n"); exit(0);
			default:
				printf("UNK terrain %d %d\n", x, y); exit(0);
		}
	}
	ind--;
}
