#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

char pipes[200][200];
long tot = 0;
int X, Y;
int chright(char *forwhat);
int chleft(char *forwhat);
int chtop(char *forwhat);
int chbtm(char *forwhat);
void printmaze();
int leny = 0;
int lenx = 0;
int distfun(int y1, int x1, int y2, int x2);
#define DAY "2023 Day11 Part2"
#define getchar();
struct coords {
	int x;
	int y;
};
int main(int argc, char **argv)
{
	int r = 0;
	char starts[100][5];
	printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
	printf("\n");
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);

	int fd = dup(1); close(1);
	char line[1000][1000];
	struct coords co[2000];
	int linenum = 0;
	while(1) {
		fgets(line[linenum], 1000, a);
		if (feof(a)) break;
		printf("LINE: %s", line[linenum]); fflush(stdout);
		linenum++;
	}
	fclose(a);

	for (int y = 0; y < linenum; y++) {
		int len = strlen(line[y]);
		for (int x = 0; x < len; x++)
		{
			if (line[y][x] == '\n') line[y][x] = '\0';
		}
	}
	//------------------------
	//findcoords();
	int pos = 0;
	for (int y = 0; y< linenum; y++) {
		for (int x = 0; x < strlen(line[0]); x++) {
			if (line[y][x] == '#') {
				co[pos].y = y;
				co[pos].x = x;
				pos++;
			}
		}
	}
	//------------------------
	// add horiz blanks
	for (int y = linenum-1; y > 0; y--) {
		for (int x = 0; x < strlen(line[0]); x++) {
			if (line[y][x] == '#') {
				break; //do nothing  
			} else {
				if (x == strlen(line[y]) - 1) {
					//printf("all dots..");
					for (int z = 0; z < pos; z++) {
						if (co[z].y > y) {
							printf("pos %d: %d,%d ", z, co[z].x, co[z].y);
							co[z].y += 999999;
							printf("to %d,%d\n ", co[z].x, co[z].y);
						}

					}
				}
			}
		}
	}

	printf("VERt..."); getchar();
	//----------------------
	// add vert blanks
	//	for (int x = 0; x < strlen(line[0]); x++)

	for (int x = strlen(line[0]) - 1; x >= 0 ; x--) {
		for (int y = 0; y < linenum; y++) {
			if (line[y][x] == '#') {
				break;
			} else {
				if (y == linenum-1) {
					// all dot at pos x, all ys
					for (int z=0; z<pos; z++) {
						if (co[z].x > x) {
							printf("pos %d: %d, %d ", z, co[z].x, co[z].y);
							co[z].x += 999999;
							printf("to: %d, %d\n ", co[z].x, co[z].y);
						}
					}
				}	
			}
		}
	}
	printf("horiz"); getchar();

	printf("***************\n");

	long dist = 0;
	for (int q1 = 0; q1 < pos; q1++) {
		printf("***************\n");
		for (int q2 = q1+1; q2 < pos; q2++) {
			dist+=distfun(co[q1].y, co[q1].x, co[q2].y, co[q2].x);
		}
	}
	printf("**** dist: %ld\n", dist);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", dist);
}
int distfun(int dy1, int dx1, int dy2, int dx2)
{
	//        printf("in distfun %d,%d -> %d,%d\n", dx1, dy1, dx2, dy2);
	int absx=abs(dx1 - dx2);
	int absy=abs(dy1 - dy2);
	printf("dist %d\n", absx + absy);

	return absx + absy;
}
