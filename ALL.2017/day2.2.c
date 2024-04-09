#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define DAY "2017 Day2.2"
int pos = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r");
	printf(DAY); printf("\n"); fflush(stdout);

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
        int jumpout = 0;
        for (int i = 0; i < NUMS; i++) {
		printf("here1..."); fflush(stdout);
		for (int j = 0; j < NUMS; j++) {
		        printf("here2..."); fflush(stdout);
			if (nums[j] > nums[i]) {
				if (nums[j] % nums[i] == 0) {
					if (nums[j] / nums[i] != 1) {
						checksum += nums[j] / nums[i];
						jumpout = 1;
					}
				}
			} else {
				if (nums[i] % nums[j] == 0) {
					if (nums[i] / nums[j] != 1) {
						checksum += nums[i] / nums[j];
						jumpout = 1;
					}
				}
			}
			if (jumpout == 1) {break;}
		}
	        if (jumpout == 1) {break;}
	}
	printf("here1..."); fflush(stdout);
}

        printf("******CHKSUM: %d\n", checksum);
}

