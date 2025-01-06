#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
int lenx = 0;
int leny = 0;
int LINE = 1000;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day15 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

        char line1[LINE];

	int nums[3000];
	int numsPos = 0;
	int starts = 0;
//0,3,6
while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	//line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);

	char *Snum = strtok(line1, ",\n");
	do {
		nums[numsPos++] = atoi(Snum);
		starts++;
	} while ((Snum = strtok(NULL, ",\n")) != NULL);
	leny++;
}
	
	for (int i = 0; i < 2020 ; i++) {
		if (i >= starts) {
			printf("i is %d\n", i);
			int found = 0;
			for (int j = 0; j < i-1; j++) {
				//printf("nums[j] V nums[i] %d V %d\n", nums[j], nums[i-1]);
				if (nums[j] == nums[i-1]) {
				
					found = 1;
					//printf("found at pos j %d (%d)\n", j, nums[i-1]);
					break;
				} 
			}
			if (found == 1) {
				int pos1 = -1, pos2 = -1;
				for (int k = i-1; k >= 0; k--) {
					if (nums[k] == nums[i-1] && pos1 == -1) {
						pos1 = k;
					} else if (nums[k] == nums[i-1] && pos2 == -1) {
						pos2 = k;
						break;
					}
				}
				assert(pos1 != -1); assert(pos2 != -1);
				nums[i] = pos1 - pos2;
				numsPos++;
			} else if (found == 0) {
				//printf("found is zero\n");
				nums[i] = 0;
				numsPos++;
			}
		}

	}
	//for (int i = 0; i < numsPos; i++) { printf("--%d\n", nums[i]); }

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", nums[2020 - 1]);
}


