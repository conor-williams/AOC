#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
char ar[102][102];
FILE *a;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2022 Day8.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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

	int totVI = 0;
	for (int y = 1; y < leny-1; y++) {
		for (int x = 1; x < lenx-1; x++) {
			int foundL = 0;
			for (int xL = 0; xL < x; xL++) {
				if (ar[y][xL] >= ar[y][x]) {
					foundL = 1; break;
				}
			}

			int foundR = 0;
			for (int xR = x+1; xR < lenx; xR++) {
				if (ar[y][xR] >= ar[y][x]) {
					foundR = 1; break;
				}
			}

			int foundU = 0;
			for (int yU = 0; yU < y; yU++) {
				if (ar[yU][x] >= ar[y][x]) {
					foundU = 1; break;
				}
			}

			int foundD = 0;
			for (int yD = y+1; yD < leny; yD++) {
				if (ar[yD][x] >= ar[y][x]) {
					foundD = 1; break;
				}
			}
			if (foundL ==0 || foundR == 0 || foundU == 0 || foundD == 0) {
				totVI++;
			}
		}
	}

	printf("***totVI %d\n", totVI);
	printf("***tot %d\n", totVI+(2*leny)+(2*(lenx-2)));

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", totVI+(2*leny)+(2*(lenx-2)));
}
