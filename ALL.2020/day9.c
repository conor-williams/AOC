#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
FILE *a;
int aR[1200];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2020 Day9 Part1\n"); fflush(stdout);

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

	int NUMS = 25;
	for (int i = NUMS; i < leny; i++) {
			int found = 0;
			for (int z = i - NUMS; z < i - 1; z++) {
				for (int q = i - NUMS + 1; q < i; q++) {
					if (aR[i] == (aR[z] + aR[q])) {
						found = 1; goto end;
					}
				}
			}
end:
			if (found == 0) {
				printf("****aR[i] is %d\n", aR[i]); 

				fflush(stdout); dup2(fd, 1);
				printf("***ans: %d\n", aR[i]); 
				exit(0);
			}
	}

}
