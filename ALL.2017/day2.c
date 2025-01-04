#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int pos = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("2017 Day2.1\n"); fflush(stdin); fflush(stdout);


	fflush(stdout); int fd = dup(1); close(1);
        char line1[3000];

int NUMS = 16;
int nums[NUMS];
int checksum = 0;
while (1) 
{
        fgets(line1, 3000, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
        sscanf(line1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &nums[0], &nums[1], &nums[2], &nums[3], &nums[4], &nums[5], &nums[6], &nums[7], &nums[8], &nums[9], &nums[10], &nums[11], &nums[12], &nums[13], &nums[14], &nums[15]);

        int bigindex = 0;
        for (int i = 0; i < NUMS; i++) {
		if (nums[i] > nums[bigindex]) {bigindex = i;}
	}
 	int smallindex = 0;
	for (int i = 0; i < NUMS; i++) {
		if (nums[i] < nums[smallindex]) {smallindex = i;}
        }
	checksum += nums[bigindex] - nums[smallindex];
}

	
	dup2(fd, 1);
        printf("******CHKSUM: %d\n", checksum);
}

