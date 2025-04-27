#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2021 Day8 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[5000];
	char *first;
	int tot = 0;
	int leny = 0;
	while (1) {
		int posC = 0;
		fgets(line1, 4999, a);
		if (feof(a)) break;
		//        line1[strlen(line1)-1] = '\0';
		printf("LINE: %s\n", line1);
		first = strtok(line1, "|");
		first = strtok(NULL, "\n");
		first = strtok(first, " ");

		do {
			posC++;
			printf("%s,", first);
			if (strlen(first) == 2 || strlen(first) == 4 || strlen(first) == 3 || strlen(first) == 7) {
				tot++;
			}
		} while ((first = strtok(NULL, " ")) != NULL);
		//getchar();
		leny++;
	}
	fclose(a);

	printf("***tot %d\n", tot);
	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", tot);
}
