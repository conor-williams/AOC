#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx, leny;
#define DAY "2019 day8 part1\n"
#undef _DEBUG_
#define MAX 15200
#define Y 6
#define X 25
#define LAY 3
int screen[200][Y][X];

int main(int argc, char **argv)
{
	lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
	fflush(stdout); int fd = dup(1); close(1);
        char line1[MAX] = {0};
	int lay = 0;
while(1) {
        fgets(line1, MAX -1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	printf("LINE: %s getchar\n", line1); getchar();
	lay = 0;
	for (int i = 0 ; i < (int)strlen(line1);) {
		for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				screen[lay][y][x] = line1[i] - 48;
				i++;
			}	
		}
		lay++;
	}
	leny++;
}
fclose(a);

	int minLAYER = -1;
	int ONE, TWO;
	int minZERO = 9999;
	for (int l = 0; l < lay; l++) {
		printf("Layer %d\n", l);
		int countZERO = 0;
		int countONE = 0;
		int countTWO = 0;
		for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				//printf("[%d]", screen[l][y][x]);
				if (screen[l][y][x] == 0) {
					countZERO++;
				} else if (screen[l][y][x] == 1) {
					countONE++;
				} else if (screen[l][y][x] == 2) {
					countTWO++;
				}
			}	
		}
		if (countZERO < minZERO) {minZERO = countZERO; ONE = countONE; TWO = countTWO; minLAYER = l;}
	}

	
	fflush(stdout); dup2(fd, 1);
	printf("***ONE*TWO %d\n", ONE*TWO);
}
