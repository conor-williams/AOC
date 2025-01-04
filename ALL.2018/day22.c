#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#undef _DEBUG_
#define SIZE 40
char line1[SIZE];
unsigned long tot = 0;

int tX, tY, depth;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day22.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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

	char (*grid)[tX+10] = malloc(sizeof(char[tY+10][tX+10]));
	if (grid == NULL) {perror("gridE\n"); exit(0);}

	int (*geo)[tX+10] = malloc(sizeof(int[tY+10][tX+10]));
	if (geo == NULL) {perror("geoE\n"); exit(0);}

	int (*ero)[tX+10] = malloc(sizeof(int[tY+10][tX+10]));
	if (ero == NULL) {perror("eroE\n"); exit(0);}

	int (*risk)[tX+10] = malloc(sizeof(int[tY+10][tX+10]));
	if (risk == NULL) {perror("riskE\n"); exit(0);}

	printf("here1"); fflush(stdout);
	geo[0][0] = 0;		
	printf("here2"); fflush(stdout);
	geo[tY][tX] = 0;
	printf("here3"); fflush(stdout);
	{
		int y = 0;
		for (int x = 0; x <= tX; x++) {
			//printf("x of X: %d of %d\n", x, tX); fflush(stdout);
			geo[y][x] = x * 16807; 
		}

		int x = 0;
		for (int y = 0; y <= tY; y++) {
			geo[y][x] = y * 48271;
		}
	}

	geo[0][0] = 0;		
	geo[tY][tX] = 0;
	{
		int y = 0;
		for (int x = 0; x <= tX; x++) {
			ero[y][x] = (geo[y][x] + depth) % 20183;
		}

		int x = 0;
		for (int y = 0; y <= tY; y++) {
			ero[y][x] = (geo[y][x] + depth) % 20183;
		}
	}
		
	
	{
		for (int y = 1; y <= tY; y++) {
			for (int x = 1; x<= tX; x++) {
                                if (x == 0 && y==0) {
                                } else if (x == tX && y==tY) {
                                } else {
                                        geo[y][x] = ero[y][x-1] * ero[y-1][x];
                                }
                                ero[y][x] = (geo[y][x] + depth) % 20183;

			}
		}
	}

	{
		for (int y = 0; y <= tY; y++) {
			for (int x = 0; x<= tX; x++) {
				if (x == 0 && y==0) {continue;}
				if (x == tX && y==tY) {continue;}
				switch(ero[y][x] % 3) {
					case 0:
						grid[y][x] = '.';
						risk[y][x] = 0;
						break;
					case 1:
						grid[y][x] = '=';
						risk[y][x] = 1;
						break;
					case 2:
						grid[y][x] = '|';
						risk[y][x] = 2;
						break;
				}
			}
		}
	}
	
	printf("after2\n");
	tot = 0;
	{
		for (int y = 0; y <= tY; y++) {
			for (int x = 0; x <= tX; x++) {
				tot += risk[y][x];			
			}
		}
	}
	free(grid); free(geo); free(ero); free(risk);

	fflush(stdout); dup2(fd, 1);
	printf("**tot %lu\n", tot);
}

