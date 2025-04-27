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

	a = fopen(argv[1], "r"); printf("		2022 Day4.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	//int lenx = 0;
	int leny = 0;
	int count = 0;
	while (1) {
		fgets(line1, 50, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';	
		int x1, y1, x2, y2;
		sscanf(line1, "%d-%d,%d-%d", &x1, &y1, &x2, &y2);
		printf("%d %d %d %d\n", x1, y1, x2, y2);
		if ((x1 <= x2 && y1 >= x2) || (x2 <= x1 && y2 >= x1)) {
			printf("overlap: %s\n", line1);
			count++;
		}
		leny++;
	}
	fclose(a);
	printf("**count is %d\n", count);

	fflush(stdout); dup2(fd, 1);
	printf("**ans is %d\n", count);
}
