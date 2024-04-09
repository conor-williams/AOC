#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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
       
        char line1[MAX] = {0};
	int lay = 0;
while(1) {
        fgets(line1, MAX -1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
	lenx = strlen(line1);
	//printf("LINE: %s getchar\n", line1); getchar();
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

	for (int y = 0; y < Y; y++) {
		for (int x = 0; x < X; x++) {
			int c; int lB = -1; int lW = -1;
			for (int l = 0; l < lay; l++) {
				if (screen[l][y][x] == 0) {
					if (lB == -1) { lB = l; }
				} else if (screen[l][y][x] == 1) {
					if (lW == -1) { lW = l; }
				} else if (screen[l][y][x] == 2) {
				}
			}
			if (lB == -1 && lW == -1) {
				printf("NO COL\n");
			} else if (lB == -1) {
				c = 1;
			} else if (lW == -1) {
				c = 0;
			} else {
				if ( lB < lW ) {
					c = 0;
				} else {
					c = 1;
				}
			}
			if (c == 0) {
				printf("0");
			} else {
				printf(" ");				
			}	
		}
		printf("\n");
	}
	printf("\n");

}
