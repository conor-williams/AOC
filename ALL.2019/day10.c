#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2019 day10 part1\n"
#undef _DEBUG_
#define MAX 2000
#define MX 100
#define MY 100
char board[MY][MY];

int X;
int Y;
int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
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
				int detectBoard[MY][MX] = {0};
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
	printf("\n***maxDetect:%d @ %d, %d\n", maxDetect, maxX, maxY);
	dup2(fd, 1);
	printf("**ans: %d\n", maxDetect);
}

