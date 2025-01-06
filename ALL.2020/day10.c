#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
int aR[1200];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2020 Day10 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];
	
int leny = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int ret;
	int num; 
	ret = sscanf(line1, "%d", &num);
	if (ret == 1) {
		aR[leny] = num;
	}
	leny++;
}
fclose(a);
	sort(aR, aR+leny);
	int jMax = aR[leny-1]+3;
	aR[leny] = jMax; leny++;
	
	int jStart = 0;
	int d[5] = {0};
	for (int i = 0; i < leny; i++) {
		int diff = 0;
		if ((diff = (aR[i] - jStart)) <= 3) {
			d[diff]++;
			jStart = aR[i];
		}
	}
	printf("diffs:\n");
	for (int j = 0; j < 4; j++) {
		printf("%d:%d\n", j, d[j]);
	}
	printf("\n");
	printf("*** MUL %d\n", d[1] * d[3]);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", d[1] * d[3]);
}
