#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#define getchar()

#define DAY "		2015 Day 2.1"
int tot = 0;
int main(int argc, char **argv)
{
        //printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r");
	printf(DAY); printf("\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);

        char line1[8000];
	int nums[3];
        int numlines = 0;
	while(1) {
		fgets(line1, 7999, a);
		if (feof(a)) break;
		numlines++;
		sscanf(line1, "%dx%dx%d", &nums[0], &nums[1], &nums[2]);
		printf("nums: %d %d %d\n", nums[0], nums[1], nums[2]); 
	        printf("This box (no slack): %d\n", 2*nums[0]*nums[1] + 2*nums[0]*nums[2] + 2*nums[1]*nums[2]);
	        tot += 2*nums[0]*nums[1] + 2*nums[0]*nums[2] + 2*nums[1]*nums[2];
		int biggest = 0, indexbiggest = 0;
		for (int f=0; f<3;f++) {
			if (nums[f] > biggest) {
				indexbiggest = f; biggest = nums[f];}
		}
		nums[indexbiggest]=1;
		printf("Slack %d\n", nums[0]*nums[1]*nums[2]);
		tot += nums[0]*nums[1]*nums[2];
		
        }
        fclose(a);

	fflush(stdout); dup2(fd, 1);
        printf("****TOT: %d\n", tot);

}
