#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
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
int main(int argc, char **argv)
{
	int r = 0;
	char starts[100][5];
	printf("%d\n", argc); printf("%s\n", argv[1]); fflush(stdin); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); printf("\n"); fflush(stdin); fflush(stdout);

	print("broken..\n"); exit(0);
	fflush(stdout); int fd = dup(1); close(1);
	//char line[10000000][10000000];
	char line[1000][1000];

	int linenum = 0;
	while(1) {
		fgets(line[linenum], 1000, a);
		if (feof(a)) break;
		printf("LINE: %s", line[linenum]); fflush(stdout);
		linenum++;
	}
	for (int y = 0; y < linenum; y++) {
		int len = strlen(line[y]);
		for (int x = 0; x < len; x++)
		{
			if (line[y][x] == '\n') line[y][x] = '\0';
		}
	}
	fclose(a);

	// add horiz blanks
	for (int i = 0; i < linenum - 1; i++) {
		for (int x = 0; x < strlen(line[0]); x++) {
			if (line[i][x] == '#') {
				break; //do nothing  
			} else {
				if (x == strlen(line[i]) - 1) {
					//printf("all dots..");
					for (int q = 0; q< 999999; q++) {
						linenum++;
						i++;
						for (int k = linenum; k > i-1; k--) {
							strcpy(line[k], line[k-1]);
						}
					}

				}
			}
		}
	}

	for (int i = 0; i < linenum; i++) {
		printf(line[i]);
		printf("\n");
	}
	//printf("VERt..."); getchar();

	// add vert blanks
	printf("streln[line[0]] is %d\n", strlen(line[0]));
	for (int x = 0; x < strlen(line[0]); x++) {
		for (int y = 0; y < linenum; y++) {
			if (line[y][x] == '#') {
				break;
			} else {
				if (y == linenum-1) {
					// all dot at pos x, all ys
					printf("got all dots in each row... xpos: %d\n", x);

					for (int q = 0; q < 999999; q++) {
						//all x's from x for all y's shift over
						for (int f = 0; f < linenum; f++) {
							//line[f][x] shifts;
							int len = strlen(line[f]) + 9;
							for (int g = len; g >= x; g--) {
								line[f][g+1] = line[f][g];
								//printf("swap %d %d\n", g+1, g);
							}
							//line[f][len] = '\0';
							//line[f][len+1] = '\0';
						}	
						x++;
					}
					for (int m = 0; m < linenum; m++) {
						printf(line[m]);
						printf("\n");
					}
					//getchar();
				}
			}
		}
	}

	for (int i = 0; i < linenum; i++) {
		printf(line[i]);
		printf("\n");
	}
	printf("***************\n");
	int dist = 0;
	for (int y1 = 0; y1 < linenum; y1++) {
		for (int x1 = 0; x1 < strlen(line[0]); x1++) {
			if (line[y1][x1] == '#') {
				printf("outer hash at: %d %d\n", y1, x1);
				printf("-----------------\n");
				int Ix2, Iy2;
				Ix2 = x1+1;
				Iy2 = y1;
				if (x1+1 == strlen(line[0])) {Ix2 = 0; Iy2++;} 
				for (int y2 = Iy2; y2 < linenum; y2++) {
					for (int x2 = Ix2; x2 < strlen(line[0]); x2++) {
						if (line[y2][x2] == '#') {
							dist += distfun(y1, x1, y2, x2);
						}
					}
					Ix2 = 0;
				}
			}
		}
	}
	printf("**** dist: %d\n", dist);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", dist);
}
int distfun(int dy1, int dx1, int dy2, int dx2)
{
	printf("in distfun %d,%d -> %d,%d\n", dx1, dy1, dx2, dy2);
	int absx=abs(dx1 - dx2);
	int absy=abs(dy1 - dy2);
	printf("dist %d\n", absx + absy);

	return absx + absy;
	/*
	   int mydist = 0;
	   if (dy1 == dy2 && dx1 == dx2) {mydist = 0;}
	   else if (dy1 == dy2) {mydist = dx2 - dx1;}
	   else if (dy1+1 == dy2) {mydist = abs(dx2 - dx1) + 1;}
	   else if (dy1+2 == dy2) {mydist = abs(dx2 - dx1) + 1;}

	   else if (dy1 == dy2) {mydist = abs(dy1 - dy2);}
	   else if (dx1 == dx2) {mydist = abs(dy1 - dy2);}
	   return mydist;
	 */
}
