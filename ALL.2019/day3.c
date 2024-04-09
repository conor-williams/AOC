#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int lenx, leny;
#define DAY "2019 day2 part1\n"
#undef _DEBUG_
/*
#define GRIDX 50
#define GRIDY 50
#define STARTX 10
#define STARTY 40
*/
#define GRIDX 35000
#define GRIDY 20000
#define STARTX 30000
#define STARTY 15000
int prevX; int prevY; 
char puz[2][GRIDY][GRIDX];
void manX();


void manX() {
		for (int y = 0; y < GRIDY; y++) {
			for (int x = 0 ; x < GRIDX; x++) {
				if (puz[1][y][x] == 'X') {
					printf("res is: %d\n", abs(STARTX - x) + abs(STARTY - y));
				}
			}
		}

}
void minmanX();
void minmanX() {
		int min = 0;
					int first = 0;
		for (int y = 0; y < GRIDY; y++) {
			for (int x = 0 ; x < GRIDX; x++) {
				if (puz[1][y][x] == 'X') {
					if (first == 0) {first = 1; min = abs(STARTX-x) + abs(STARTY-y);}
					if ((abs(STARTX -x) + abs(STARTY-y)) < min) {
						min = abs(STARTX -x) + abs(STARTY-y);
					}
				}
			}
		}
		printf("min is %d\n", min);

}
void printpuzzle();
void printpuzzle() {
		for (int y = 0; y < GRIDY; y++) {
			for (int x = 0 ; x < GRIDX; x++) {
				printf("%c", puz[1][y][x]);
			}
			printf("\n");
		}
}
void dotpuzzle();

void dotpuzzle()
{
		for (int y = 0; y < GRIDY; y++) {
			for (int x = 0 ; x < GRIDX; x++) {
				puz[0][y][x] = '.';
				puz[1][y][x] = '.';
			}
		}
}
int main(int argc, char **argv)
{
	dotpuzzle();
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[3000];
	int wire = 0;
while(1) {

	prevX = STARTX; prevY = STARTY;
	int num = 0;
	wire++;
        fgets(line1, 2990, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
#ifdef _DEBUG_
	printf("LINE: %s getchar\n", line1); getchar();
#endif
	char *token = strtok(line1, ",\n");
	while (token != NULL) {
		char tokenRLUD = token[0];
		token[0] = ' ';
		num = atoi(token);
//printf("num %d getchar\n", num); getchar();
		switch(tokenRLUD) {
			case 'R':
				for (int x = prevX+1; x <= num+prevX; x++) {
					if (x >= GRIDX) {printf("pos warning X"); fflush(stdout);exit(0);}
					if (wire == 2) {
						if (puz[0][prevY][x] == '|') {
								puz[1][prevY][x] = 'X';
						} else {
								puz[1][prevY][x] = '-';
						} 
					} else if (wire == 1) {
						puz[0][prevY][x] = '-';
					}
				}
				prevX = num+prevX;
				break;
			case 'L':
				for (int x = prevX-1; x >= prevX-num; x--) {
					if (x < 0) {printf("neg warning X"); fflush(stdout);exit(0);}
					if (wire == 2) {
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
					if (wire == 2) {
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
					if (wire == 2) {
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
				printf("ERROR - exit\n"); fflush(stdout); exit(0);
		}
		token = strtok(NULL, ",\n");
		leny++;
	}
	
	printf("lenx %d - leny %d\n", lenx, leny);
}
if (GRIDX == 50) {printpuzzle();}
manX();
minmanX();
fclose(a);

	//printf("******** tot %ld\n", tot);
}
