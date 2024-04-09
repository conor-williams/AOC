#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int pos;
int lenx, leny;
#define DAY "2019 day2 part1\n"
#undef _DEBUG_
struct posmin {
	int x;
	int y;
	int man;
	int stepsW1;
	int stepsW2;
};
struct posmin points[1000];
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
void recordW1(int x, int y, int man, int stepsW1);
void recordW1(int x, int y, int man, int stepsW1) {
	for (int i = 0; i < pos; i++) {
		if (points[i].x == x && points[i].y == y) {
			points[i].stepsW1 = stepsW1;
			break;
		}

	}
}
void recordW2(int x, int y, int man, int stepsW2);
void recordW2(int x, int y, int man, int stepsW2) {

	points[pos].x = x;	
	points[pos].y = y;
	points[pos].man = man;
	points[pos].stepsW2 = stepsW2;
	pos++;
}
int man2X();
int man2X(int x, int y) {
	return abs(STARTX - x) + abs(STARTY - y);

}
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
	pos = 0;
       
        char line1[3000];
	int wire = 0;
	int stepsW1 = 0; int stepsW2 = 0;
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
						stepsW2++;
						if (puz[0][prevY][x] == '|') {
								puz[1][prevY][x] = 'X';
								puz[0][prevY][x] = 'X'; recordW2(x, prevY, man2X(x, prevY), stepsW2);
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
						stepsW2++;
						if (puz[0][prevY][x] == '|') {
							puz[1][prevY][x] = 'X';
							puz[0][prevY][x] = 'X'; recordW2(x, prevY, man2X(x, prevY), stepsW2);
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
						stepsW2++;
						if (puz[0][y][prevX] == '-') {
							puz[1][y][prevX] = 'X';
							puz[0][y][prevX] = 'X'; recordW2(prevX, y, man2X(prevX, y), stepsW2);
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
						stepsW2++;
						if (puz[0][y][prevX] == '-') {
							puz[1][y][prevX] = 'X';
							puz[0][y][prevX] = 'X'; recordW2(prevX, y, man2X(prevX, y), stepsW2);
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
fclose(a);
a = fopen(argv[1], "r"); 
wire = 0;
//second while
while (1) {
	stepsW1 = 0;
	prevX = STARTX; prevY = STARTY;
	int num = 0;
	wire++;
	int steps = 0;
	int foundX = 0;
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
					if (wire == 1) {
						stepsW1++;
						if (puz[0][prevY][x] == 'X') {
							foundX = 1; recordW1(x, prevY, 0, stepsW1);
						} else {

						} 
					}
				}
				prevX = num+prevX;
				break;
			case 'L':
				for (int x = prevX-1; x >= prevX-num; x--) {
					if (x < 0) {printf("neg warning X"); fflush(stdout);exit(0);}
					if (wire == 1) {
						stepsW1++;
						if (puz[0][prevY][x] == 'X') {
							foundX = 1; recordW1(x, prevY, 0, stepsW1);
						} else {
						}
					}
						
				}
				prevX = prevX - num;
				break;
			case 'U':
				for (int y = prevY-1; y >= prevY-num; y--) {
					if (y < 0) {printf("neg warning y"); fflush(stdout); exit(0);}
					if (wire == 1) {
						stepsW1++;
						if (puz[0][y][prevX] == 'X') {
							foundX = 1; recordW1(prevX, y, 0, stepsW1);
						} else {
						}
					}
						
				}
				prevY = prevY - num;
				break;
			case 'D':
				for (int y = prevY+1; y <= prevY+num; y++) {
					if (y >= GRIDY) {printf("pos warning y"); fflush(stdout); exit(0);}
					if (wire == 1) {
						stepsW1++;
						if (puz[0][y][prevX] == 'X') {
							foundX = 1; recordW1(prevX, y, 0, stepsW1); 
						} else {
						}
					}
				}
				prevY = prevY + num;
				break;
			default:
				printf("ERROR - exit\n"); fflush(stdout); exit(0);
		}
		token = strtok(NULL, ",\n");
		leny++;
		
//		if (foundX == 1) {printf("steps is %d\n", steps); break;}
	}
}


int posminman = 0;
int first = 0;
int minman2 = 0;
for (int i = 0; i < pos; i++) {
	if (first == 0) {first = 1; posminman = 0; minman2 = points[pos].man;}
	if (points[i].man < minman2) {minman2 = points[i].man; posminman = pos; }
	printf("x: %d y: %d man: %d stepsW1: %d stepsW2: %d W1+W2 %d\n", 
		points[i].x, points[i].y, points[i].man, points[i].stepsW1, points[i].stepsW2, points[i].stepsW1+points[i].stepsW2);
	
}
int posminsum = 0;
int minsum;
for (int i = 0; i < pos; i++) {
	if (first == 0) {first = 1; posminsum = 0; minsum = points[0].stepsW1 + points[0].stepsW2;}
	if (points[i].stepsW1 + points[i].stepsW2 < minsum) {minsum = points[i].stepsW1 + points[i].stepsW2; posminsum = i; }
	printf("x: %d y: %d man: %d stepsW1: %d stepsW2: %d W1+W2 %d\n", 
		points[i].x, points[i].y, points[i].man, points[i].stepsW1, points[i].stepsW2, points[i].stepsW1+points[i].stepsW2);
	
}
printf("**min steps wire 1 + wire 2= %d\n", points[posminsum].stepsW1 + points[posminsum].stepsW2);



if (GRIDX == 50) {printpuzzle();}
manX();
minmanX();
fclose(a);

	//printf("******** tot %ld\n", tot);
}
