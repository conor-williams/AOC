#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
char ar[300][60];
FILE *a;
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2022 Day3.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];

//int lenx = 0;
int leny = 0;
while (1) {
        fgets(line1, 50, a);
        printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1)-1] = '\0';	
	strcpy(ar[leny], line1);
	leny++;
}
fclose(a);
int tot = 0;
int count = 0;
for (int y = 0; y < leny; y++) {
	char matchList[300];
	int matchListLen = 0;
	for (int x1 = 0; x1 < (int)strlen(ar[y])/2; x1++) {
		for (int x2 = (int)strlen(ar[y])/2; x2 < (int)strlen(ar[y]); x2++) {
			if (ar[y][x1] == ar[y][x2]) {
				int found1 = 0;
				for (int m = 0; m < matchListLen; m++) {
					if (ar[y][x1] == matchList[m]) { found1 = 1; break; }
				}
				if (found1 == 0) {
					matchList[matchListLen] = ar[y][x1]; matchListLen++;
					printf("match %c\n", ar[y][x1]);
					count++;
					       if (islower((int)ar[y][x1])) {
						printf("adding lower %d\n", ((int)ar[y][x1] - 96));
						tot = tot + ((int)ar[y][x1] - 96);
					} else if (isupper((int)ar[y][x1])) {
						printf("adding upper %d\n", ((int)ar[y][x1] - 64+26));
						tot = tot + ((int)ar[y][x1] - 64+26);
					} else {
						printf("error..."); exit(0);
					}
				}
			}	
		}
	}
}
	printf("***tot %d\n", tot);
	printf("***count %d\n", count);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", tot);
}
