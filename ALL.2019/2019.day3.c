#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <unistd.h>

using namespace std;
#define getchar()
int lenx, leny;
#define DAY "		2019 day3 part1\n"
#undef _DEBUG_
/*
#define GRIDX 50
#define GRIDY 50
#define STARTX 10
#define STARTY 40
*/
/*
#define GRIDX 40000
#define GRIDY 20000
#define STARTX 30000
#define STARTY 15000
*/
int GRIDX;
int GRIDY;
int STARTX;
int STARTY;

int prevX; int prevY; 
int fd;
//void manX(char puz[][]);
//void minmanX(char puz[][]);
//void printpuzzle();
//void dotpuzzle();

int main(int argc, char **argv)
{
	//dotpuzzle();
	lenx = 0; leny = 0;
	///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	char line1[3000];
	int wire = 0;
	char lines[2][3000];
	int startx = 0;
	int starty = 0;
	int minX = 99999999;
	int minY = 99999999;
	int maxX = 0;
	int maxY = 0;
	int pX = 0; int pY = 0;
	while (1) {
		pX = 0;
		pY = 0;
		printf("and again..>");
		int num = 0;
		fgets(line1, 2990, a);
		if (feof(a)) break;
		line1[strlen(line1) -1]='\0';
		strcpy(lines[wire], line1);
		lenx = strlen(line1);
		printf("%s\n", lines[wire]); fflush(stdout);
		char *token = strtok(line1, ",\0");
		while (token != NULL) {
			char tokenRLUD = token[0];
			token[0] = ' ';
			//printf("%s\n", token);
			num = atoi(token);
			printf("%d\n", num);
			switch(tokenRLUD) {
				case 'R':
					pX+=num;
					break;
				case 'L':
					pX-=num;
					break;
				case 'U':
					pY-=num;
					break;
				case 'D':
					pY+=num;
					break;
			}
			if (pX > maxX) {maxX = pX;}
			if (pX < minX) {minX = pX;}
			if (pY > maxY) {maxY = pY;}
			if (pY < minY) {minY = pY;}
			token = strtok(NULL, ",\0");
			printf("new token???"); fflush(stdout);
		}
		printf("here2..");
		wire++;
	}
	fclose(a);
	printf("after... \n"); fflush(stdout);
	printf("%d %d %d %d\n", minX, maxX, minY, maxY);
	/*#define GRIDX 40000
#define GRIDY 20000
#define STARTX 30000
#define STARTY 15000
*/
	printf("here4...."); fflush(stdout);
	GRIDX = maxX-minX+30;
	GRIDY = maxY-minY+30;
	printf("GS: %d %d\n", GRIDX, GRIDY); fflush(stdout);

	printf("here11\n"); fflush(stdout);
	//char puz[2][GRIDY][GRIDX];
	map <int, map <int, char>> puz[2];

	printf("here12\n"); fflush(stdout);
	STARTX=abs(minX)+15;
	STARTY=abs(minY)+15;
	printf("here10..."); fflush(stdout);

	/*
	for (int y = 0; y < GRIDY; y++) {
		for (int x = 0 ; x < GRIDX; x++) {
			puz[0][y][x] = '.';
			puz[1][y][x] = '.';
		}
	}
	*/

	wire = 0;

	printf("here8\n"); fflush(stdout);
	while(1) {
		if (wire == 2) {break;}
		printf("and again...");
		prevX = STARTX; prevY = STARTY;
		int num = 0;
		lenx = strlen(lines[wire]);

		char *token = strtok(lines[wire], ",\0");
		printf("lineslineslines...%s\n", lines[wire]);
		while (token != NULL) {
			char tokenRLUD = token[0];
			printf("%c\n", tokenRLUD);
			token[0] = ' ';
			num = atoi(token);
			printf("num %d getchar\n", num); 
			switch(tokenRLUD) {
				case 'R':
					for (int x = prevX+1; x <= num+prevX; x++) {
						if (x >= GRIDX) {printf("pos warning X"); fflush(stdout);exit(0);}
						if (wire == 1) {
							if (puz[0][prevY][x] == '|') {
								puz[1][prevY][x] = 'X';
							} else {
								puz[1][prevY][x] = '-';
							} 
						} else if (wire == 0) {
							puz[0][prevY][x] = '-';
						}
					}
					prevX = num+prevX;
					break;
				case 'L':
					for (int x = prevX-1; x >= prevX-num; x--) {
						if (x < 0) {printf("neg warning X"); fflush(stdout);exit(0);}
						if (wire == 1) {
							if (puz[0][prevY][x] == '|') {
								puz[1][prevY][x] = 'X';
							} else {
								puz[1][prevY][x] = '-';
							}
						} else {
							puz[0][prevY][x] = '-';
						}

					}
					prevX = prevX - num;
					break;
				case 'U':
					for (int y = prevY-1; y >= prevY-num; y--) {
						if (y < 0) {printf("neg warning y"); fflush(stdout); exit(0);}
						if (wire == 1) {
							if (puz[0][y][prevX] == '-') {
								puz[1][y][prevX] = 'X';
							} else {
								puz[1][y][prevX] = '|';
							}
						} else {
							puz[0][y][prevX] = '|';
						}

					}
					prevY = prevY - num;
					break;
				case 'D':
					for (int y = prevY+1; y <= prevY+num; y++) {
						if (y >= GRIDY) {printf("pos warning y"); fflush(stdout); exit(0);}
						if (wire == 1) {
							if (puz[0][y][prevX] == '-') {
								puz[1][y][prevX] = 'X';
							} else {
								puz[1][y][prevX] = '|';
							}
						} else {
							puz[0][y][prevX] = '|';
						}
					}
					prevY = prevY + num;
					break;
				default:
					printf("%c\n", tokenRLUD);
					printf("%d\n", num);
					printf("ERROR - exit\n"); fflush(stdout); exit(0);
			}
			token = strtok(NULL, ",\0");
			leny++;
		}
		wire++;

		printf("lenx %d - leny %d\n", lenx, leny);
		printf("do i go again.. wire %d.", wire); fflush(stdout);
	}
	printf("here2...");
	//if (GRIDX == 50) {printpuzzle();}
	//manX(puz);
	//minmanX(puz);
	int min = 9999999;
	int first = 0;
	//for (int y = 0; y < GRIDY; y++)  for (int x = 0 ; x < GRIDX; x++) 
	for (auto y: puz[1]) {
		for (auto x: y.second) {
			if (puz[1][y.first][x.first] == 'X') {
				printf("found X");
				if (first == 0) {first = 1; min = abs(STARTX-x.first) + abs(STARTY-y.first);}
				if ((abs(STARTX -x.first) + abs(STARTY-y.first)) < min) {
					min = abs(STARTX -x.first) + abs(STARTY-y.first);
				}
			}
		}
	}
	fflush(stdout); dup2(fd,1);
	//printf("min is %d\n", min);
	printf("**ans: %d\n", min);

}
