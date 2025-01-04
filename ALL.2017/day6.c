#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("2017 Day6.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[3000];

int NUMS = 16;
int nums[NUMS];
int numsMEM[20000][NUMS];
int numsMEMPos = 0;
int leny = 0;
while (1) 
{
        fgets(line1, 3000, a);
	if (feof(a)) break;
 	printf("line1 %s\n", line1);
 	line1[strlen(line1)-1] = '\0';
        //sscanf(line1, "%d	%d	%d	%d", &nums[0], &nums[1], &nums[2], &nums[3]);
        sscanf(line1, "%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d	%d", &nums[0], &nums[1], &nums[2], 
&nums[3], 
&nums[4], 
&nums[5], 
&nums[6], 
&nums[7], 
&nums[8], 
&nums[9], 
&nums[10], 
&nums[11], 
&nums[12], 
&nums[13], 
&nums[14], 
&nums[15]

);
	leny++;
}
	
	for (int j = 0; j< NUMS; j++) {
		numsMEM[numsMEMPos][j] = nums[j];
	}
	numsMEMPos++;
	int steps = 0;
	while (1) {
//////////////
		printf("stack: ");
		int tot = 0;
		for (int i = 0; i < NUMS; i++) {
			printf(" %d ", nums[i]);	
			tot+=nums[i];
		
		}
		printf("tot[%d]\n", tot);
///////////
		steps++;
		int maxind = 0;
		for (int i = 0; i < NUMS; i++) {
			if (nums[i] > nums[maxind]) {maxind = i;}
		}
		int plusAll = nums[maxind];
		//plusAll = nums[maxind] / (NUMS-1);
		for (int i = maxind+1; ; i++) {
			i = i %NUMS;
			nums[i]++;
			nums[maxind]--;
			plusAll--;
			if (plusAll == 0) {break;}
		}
/*
		for (int i = 0; i < NUMS; i++) {
			if (i == maxind) {
				continue;
			} else {
				nums[i] += plusAll;
			}
		}
		if (plusAll == 0) {
			int end;
			if (nums[maxind] > maxind) {
				end = nums[maxind] +1;
			} else {
				end = nums[maxind];
			}
				
			for (int z = 0; z < end; z++) {
				if (z == maxind) {
					continue;
				} else {
					nums[z]++;
				}
			}
			nums[maxind] = 0;
		} else {
			nums[maxind] -= plusAll*(NUMS-1);
		}
*/
		for (int j = 0; j< NUMS; j++) {
			numsMEM[numsMEMPos][j] = nums[j];
		}
		numsMEMPos++;

		for (int k = 0; k < numsMEMPos-1; k++) {
			int found = 1;
			for (int j = 0; j < NUMS; j++) {
				if (numsMEM[k][j] != numsMEM[numsMEMPos-1][j]) {
					found = 0; break;	
				}
			}
			if (found == 1) {
				printf("MEMStack:\n");
//////////////
		for (int k = 0; k < numsMEMPos; k++) {
		int tot2 = 0;
		printf("StackMEM[%d]: ", k);
		for (int i = 0; i < NUMS; i++) {
			printf(" %3d ", numsMEM[k][i]);	
			tot2+=numsMEM[k][i];
		}
		printf("tot: %d\n", tot2);
		} printf("\n");
///////////
				printf("thats the end... [%d]", steps);
				fflush(stdout);
				dup2(fd, 1);
				printf("**ans: [ %d ]", steps); exit(0);
			}
		}
	}
}

