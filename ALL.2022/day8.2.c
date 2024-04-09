#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char ar[102][102];
FILE *a;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2022 Day3\n"); fflush(stdout);
        char line1[1000];

int lenx = 0;
int leny = 0;
while (1) {
        fgets(line1, 999, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1)-1] = '\0';	

	strcpy(ar[leny], line1);
	leny++;
}
lenx = strlen(ar[0]);

fclose(a);

	int ans = 0;
	int maxAns = 0;
	int mX, mY;
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			int foundL = 0;
			for (int xL = x-1; xL >=0 ; xL--) {
				if (ar[y][xL] >= ar[y][x]) {
					foundL++; break;
				} else {
					foundL++;
				}
			}

			int foundR = 0;
			for (int xR = x+1; xR < lenx; xR++) {
				if (ar[y][xR] >= ar[y][x]) {
					foundR++; break;
				} else {
					foundR++;
				}
				
			}
				
			int foundU = 0;
			for (int yU = y-1; yU >= 0; yU--) {
				if (ar[yU][x] >= ar[y][x]) {
					foundU++; break;
				} else {
					foundU++;
				}
			}

			int foundD = 0;
			for (int yD = y+1; yD < leny; yD++) {
				if (ar[yD][x] >= ar[y][x]) {
					foundD++; break;
				} else {
					foundD++;
				}
			}
			if (x == 2 && y == 3) {printf("%d %d %d %d\n", foundL, foundR, foundU, foundD);}
			ans = foundL * foundR * foundU * foundD;
			if (ans > maxAns) {maxAns = ans; mX = x; mY = y;}
		}
	}

printf("***maxAns %d (%d %d)\n", maxAns, mX, mY);
}
