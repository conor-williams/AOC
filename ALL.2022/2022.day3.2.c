#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
char ar[300][60];
char lines[4][1000];
FILE *a;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2022 Day3.2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];
	unsigned long tot = 0;
	//int lenx = 0;
	int leny = 0;
	while (1) {
		fgets(line1, 50, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';	
		strcpy(lines[leny%3], line1);
		if (leny % 3 == 2) {
			for (int i = 0; i < (int)strlen(lines[0]); i++) {
				for (int j = 0; j < (int)strlen(lines[1]); j++) {
					for (int k = 0; k < (int)strlen(lines[2]); k++) {
						char asdf;
						if (lines[2][k] == lines[1][j] && lines[2][k] == lines[0][i]) {
							asdf = lines[2][k];
							printf("asdf: [%c]\n", asdf);
							if (islower((int)asdf)) {
								tot += (int)asdf - 96;
							} else if (isupper((int)asdf)) {
								tot += (int)asdf - 64+26;
							} else {
								printf("error..."); exit(0);
							}
							goto out;
						}
					}	
				}
			}
		}
out:
		leny++;
	}
	fclose(a);
	printf("***tot %lu\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %lu\n", tot);
}
