#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

using namespace std;

int lenx, leny;
#define DAY "2019 day10 part2\n"
#undef _DEBUG_
#define MAX 2000
#define MX 100
#define MY 100
char board[MY][MY];
int detectBoard[MY][MX] = {0};

struct mytanit {
	int x;
	int y;
	double mytan;
};

struct mytanit z1;
struct mytanit zList[1000] = {0};
int zListPos = 0;
int X;
int Y;
int zap = 0;
struct mytanit zapit[400] = {0};
int loop(int x, int y, int xA, int yA);
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[MAX] = {0};
while(1) {
        fgets(line1, MAX -1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	printf("LINE: %s getchar\n", line1); //getchar();
	strcpy(board[leny], line1);
	leny++;
}
fclose(a);

	Y = leny;
	X = strlen(line1);	
	int maxDetect = 0; int maxX = -1, maxY = -1;
	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			int detect = 0;
			if (board[y][x] != '#') {
				//ignore
			} else {
				printf("x is %d, y is %d\n", x, y);
                                for (int iX = 0; iX < MX; iX++) {
                                        for (int iY = 0; iY < MY; iY++) {
                                                detectBoard[iY][iX] = 0;
                                        }
                                }

				for (int xR = x+1; xR < X; xR++) {
					if (board[y][xR] == '#') {	
						detectBoard[y][xR] = 1;
						detect++; break;
					}
				}
				for (int yD = y+1; yD < Y; yD++) {
					if (board[yD][x] == '#') {	
						detectBoard[yD][x] = 1;
						detect++; break;
					}
				}
				for (int xL = x-1; xL >= 0; xL--) {
					if (board[y][xL] == '#') {	
						detectBoard[y][xL] = 1;
						detect++; break;
					}
				}
				for (int yU = y-1; yU >= 0; yU--) {
					if (board[yU][x] == '#') {	
						detectBoard[yU][x] = 1;
						detect++; break;
					}
				}
				//// angled spokes...
				///
				//x+1 y+1, x+2, y+2 45degrees
				//x+1, y+2, x+2, y+4
				//x+1, y+3, x+2, y+3
				printf("detect + %d (x, y, %d %d)\n", detect, x, y); 
				for (int xA = -1; xA > -X; xA--) {
					//printf("-----VVVV-------- new XA------------\n");
					for (int yA = -1; yA > -Y; yA--) {
						int found = 0;
						for (int z = 1; z < Y; z++) {
							int xC = x + z*xA; int yC = y + z*yA;
							if (xC < 0 || yC < 0 || xC >= X || yC >= Y) {
								continue;
							}
							//printf("next (loop here with z;%d trying %d, %d\n", z, xC, yC);
							if (board[yC][xC] == '#') {
								if (found == 0 && detectBoard[yC][xC] != 1) {detect++;}
								found = 1; detectBoard[yC][xC] = 1;
							}
						}
					}
				}
				for (int xA = -1; xA > -X; xA--) {
					//printf("-----VVVV-------- new XA------------\n");
					for (int yA = 1; yA < Y; yA++) {
						int found = 0;
						for (int z = 1; z < Y; z++) {
							int xC = x + z*xA; int yC = y + z*yA;
							if (xC < 0 || yC < 0 || xC >= X || yC >= Y) {
								continue;
							}
							//printf("next (loop here with z;%d trying %d, %d\n", z, xC, yC);
							if (board[yC][xC] == '#') {
								if (found == 0 && detectBoard[yC][xC] != 1) {detect++;}
								found = 1; detectBoard[yC][xC] = 1;
							}
						}
					}
				}
				for (int xA = 1; xA < X; xA++) {
					///printf("-----VVVV-------- new XA------------\n");
					for (int yA = 1; yA < Y; yA++) {
						int found = 0;
						for (int z = 1; z < Y; z++) {
							int xC = x + z*xA; int yC = y + z*yA;
							if (xC < 0 || yC < 0 || xC >= X || yC >= Y) {
								continue;
							}
							//printf("next (loop here with z;%d trying %d, %d\n", z, xC, yC);
							if (board[yC][xC] == '#') {
								if (found == 0 && detectBoard[yC][xC] != 1) {detect++;}
								found = 1; detectBoard[yC][xC] = 1;
							}
						}
					}
				}
				for (int xA = 1; xA < X; xA++) {
					///printf("-----VVVV-------- new XA------------\n");
					for (int yA = -1; yA > -Y; yA--) {
						int found = 0;
						for (int z = 1; z < Y; z++) {
							int xC = x + z*xA; int yC = y + z*yA;
							if (xC < 0 || yC < 0 || xC >= X || yC >= Y) {
								continue;
							}
							//printf("next (loop here with z;%d trying %d, %d\n", z, xC, yC);
							if (board[yC][xC] == '#') {
								if (found == 0 && detectBoard[yC][xC] != 1) {detect++;}
								found = 1; detectBoard[yC][xC] = 1;
							}
						}
					}
				}
				printf("detectAFTER + %d (x, y, %d %d)\n", detect, x, y);
				if (detect > maxDetect) {maxDetect = detect; maxX = x; maxY = y;}
			}	
		}
	}
	printf("\n***maxDetect:%d @ %d, %d (%d, %d)\n", maxDetect, maxX, maxY, X, Y);
//CONOR
	zap = 0;
	int x = maxX; int y = maxY;
        while (zap < 301) {
			x = maxX; y = maxY;
			if (board[y][x] != '#') {
				//ignore
			} else {
				//printf("x is %d, y is %d\n", x, y);
				for (int iX = 0; iX < MX; iX++) {
					for (int iY = 0; iY < MY; iY++) {
						detectBoard[iY][iX] = 0;
					}
				}
////////////////			///////////////// 		///////////////
///
				for (int yU = y-1; yU >= 0; yU--) {
					if (board[yU][x] == '#') {	
						detectBoard[yU][x] = 1;
						board[yU][x] = ' ';
						zap++; zapit[zap].x = x; zapit[zap].y = yU; printf("%d %d,%d\n", zap, x, yU); break;
					}
				}
				double myList[1000];
{ //top right
				zListPos = 0;
				for (int xA = 1; xA < X; xA++) {
					for (int yA = -1; yA > -Y; yA--) {
						if (loop(x, y, xA, yA) == 1) {
							zList[zListPos].x = z1.x;
							zList[zListPos].y = z1.y;
							zList[zListPos].mytan = z1.mytan; zListPos++;
						}
					}
				}
				printf("zListPos == %d\n", zListPos); //getchar();

				for (int u = 0; u < zListPos; u++) {
					myList[u] = zList[u].mytan;
				}

				if (zListPos > 0) {
					sort(myList, myList+zListPos);
					for (int u = 0; u < zListPos; u++) {
						printf(" %f ", myList[u]);
					}
					printf("\n");
					
					for (int q = zListPos-1; q >= 0; q--) {
						for (int r = 0; r < zListPos; r++) {
							if (zList[r].mytan == myList[q]) {
								zap++;
								zapit[zap].x = zList[r].x;
								zapit[zap].y = zList[r].y;
								printf("zap: %d  %d, %d tan:(%f)\n", zap, zList[r].x, zList[r].y, zList[r].mytan);
							}

						}
					}
				}
				//getchar();
				printf("after top right\n"); //getchar();
}
				for (int xR = x+1; xR < X; xR++) {
					if (board[y][xR] == '#') {	
						detectBoard[y][xR] = 1;
						board[y][xR] = ' ';
						zap++;  printf("%d %d,%d\n", zap, xR, y); break;
						zapit[zap].x = xR;
						zapit[zap].y = y;
					}
				}
				for (int iX = 0; iX < MX; iX++) {
					for (int iY = 0; iY < MY; iY++) {
						detectBoard[iY][iX] = 0;
					}
				}
{
//bottom right
				zListPos = 0;
				
				for (int xA = 1; xA < X; xA++) {
					for (int yA = 1; yA < Y; yA++) {
						if (loop(x, y, xA, yA) == 1) {
							zList[zListPos].x = z1.x;
							zList[zListPos].y = z1.y;
							zList[zListPos].mytan = z1.mytan; zListPos++;
						}
					}
				}
				printf("zListPos BR == %d\n", zListPos); //getchar();
				if (zListPos > 0) {
					for (int u = 0; u < zListPos; u++) {
						myList[u] = zList[u].mytan;
					}
					sort(myList, myList+zListPos);
					for (int q = 0; q < zListPos; q++) {
						for (int r = 0; r < zListPos; r++) {
							if (zList[r].mytan == myList[q]) {
								zap++;
								zapit[zap].x = zList[r].x;
								zapit[zap].y = zList[r].y;
								printf("t (BR): %d  %d, %d tan:(%f)\n", zap, zList[r].x, zList[r].y, zList[r].mytan);
							}

						}
					}
				}
				//getchar();
}
				for (int yD = y+1; yD < Y; yD++) {
					if (board[yD][x] == '#') {	
						detectBoard[yD][x] = 1;
						board[yD][x] = ' ';
						zap++;
						zapit[zap].x = x;
						zapit[zap].y = yD;
						printf("%d %d,%d\n", zap, x, yD); break;
					}
				}
				for (int iX = 0; iX < MX; iX++) {
					for (int iY = 0; iY < MY; iY++) {
						detectBoard[iY][iX] = 0;
					}
				}
///bottom left
{
				zListPos = 0;
					for (int yA = 1; yA < Y; yA++) {
					for (int xA = -1; xA > -X; xA--) {
						if (loop(x, y, xA, yA) == 1) {
							zList[zListPos].x = z1.x;
							zList[zListPos].y = z1.y;
							zList[zListPos].mytan = z1.mytan; zListPos++;
						}
					}
				}
				printf("zListPos BL == %d\n", zListPos); //getchar();
				if (zListPos > 0) {
					for (int u = 0; u < zListPos; u++) {
						myList[u] = zList[u].mytan;
					}
					sort(myList, myList+zListPos);
					for (int q = zListPos-1; q >= 0; q--) {
						for (int r = 0; r < zListPos; r++) {
							if (zList[r].mytan == myList[q]) {
								zap++;
								zapit[zap].x = zList[r].x;
								zapit[zap].y = zList[r].y;
								printf("t (BL): %d  %d, %d tan:(%f)\n", zap, zList[r].x, zList[r].y, zList[r].mytan);
							}

						}
					}
				}

				//getchar();
}
				for (int xL = x-1; xL >= 0; xL--) {
					if (board[y][xL] == '#') {	
						detectBoard[y][xL] = 1;
						board[y][xL] = ' ';
						zap++;  printf("%d %d,%d\n", zap, xL, y); break;
					}
				}
				for (int iX = 0; iX < MX; iX++) {
					for (int iY = 0; iY < MY; iY++) {
						detectBoard[iY][iX] = 0;
					}
				}
{
//// top left
				zListPos = 0;
				for (int xA = -1; xA > -X; xA--) {
				for (int yA = -1; yA > -Y; yA--) {
						if (loop(x, y, xA, yA) == 1) {
							zList[zListPos].x = z1.x;
							zList[zListPos].y = z1.y;
							zList[zListPos].mytan = z1.mytan; zListPos++;
						}

					}
				}
				printf("zListPos TL == %d\n", zListPos); //getchar();
				if (zListPos > 0) {
					for (int u = 0; u < zListPos; u++) {
						myList[u] = zList[u].mytan;
					}
					sort(myList, myList+zListPos);
					for (int q = 0; q < zListPos; q++) {
						for (int r = 0; r < zListPos; r++) {
							if (zList[r].mytan == myList[q]) {
								zap++;
								zapit[zap].x = zList[r].x;
								zapit[zap].y = zList[r].y;
								printf("t (TL): %d  %d, %d tan:(%f)\n", zap, zList[r].x, zList[r].y, zList[r].mytan);
							}

						}
					}
				}

}
			}	
			if (zap > 200) {printf("ANS: %d\n", zapit[200].x*100 + zapit[200].y); getchar(); getchar();}
		}
}

int loop(int x, int y, int xA, int yA) {
	int found = 0; int foundZap = 0;
	for (int z = 1; z < Y; z++) {
		int xC = x + z*xA; int yC = y + z*yA;
		if (xC < 0 || yC < 0 || xC >= X || yC >= Y) {
			continue;
		}
		if (board[yC][xC] == '#') {
			if (found == 0 && detectBoard[yC][xC] != 1) {board[yC][xC]='.'; z1.x = xC; z1.y = yC; z1.mytan = abs((double)(yC -y)/(double)(xC-x)); foundZap=1; /*printf("was: Z: %d %d,%d\n", zap, xC, yC);*/}
			found = 1; detectBoard[yC][xC] = 1;
		}
	}
	return foundZap;
	
}
