#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int nums[1000][30];
long tot = 0;
int TOTNUMS = 5;
int LEVEL;
int done;
int notallzeroes = 0;
void subnums();
void transferandcalc();

void main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day9.1\n"); fflush(stdin); fflush(stdout);

        char line1[1000];
        while (1) {
done = 0;
            fgets(line1, 1000, a); if (feof(a)) {break;}
	    sscanf(line1, "%d %d %d %d %d %d", &nums[0][0], &nums[0][1], &nums[0][2], &nums[0][3], &nums[0][4], &nums[0][5]);
//            printf("line1 %s %d %d\n", line1, nums[0][0], nums[0][5]);
            printf("line1 %s\n", line1);
	    getchar();
//printf("nums[0][0] is %d\n", nums[0][0]); printf("nums[0][1] is %d\n", nums[0][1]); printf("nums[0][2] is %d\n", nums[0][2]); printf("nums[0][3] is %d\n", nums[0][3]); printf("nums[0][4] is %d\n", nums[0][4]); printf("nums[0][5] is %d\n", nums[0][5]);
///////////////////////////////////////////////////////////////////////////////////////////////



notallzeroes = 1; LEVEL = 1;

{ 
	subnums();
///LEVEL NOW 2
printf("nums[1][0] is %d\n", nums[1][0]); printf("nums[1][1] is %d\n", nums[1][1]); printf("nums[1][2] is %d\n", nums[1][2]); printf("nums[1][3] is %d\n", nums[1][3]); printf("nums[1][4] is %d\n", nums[1][4]);

/*
	        if (done != 1 && notallzeroes == 0) {
	            printf("calculating as all zeroes...");
		    // calculate
		    done = 1;
	        }
*/
}

for (int q = 1; q <= TOTNUMS-2 ; q++) 
{
printf("in loop...");
            subnums();
	    if (done != 1 && notallzeroes == 0) { 

		nums[q][TOTNUMS-q+1] = nums[q][TOTNUMS-q];
		//nums[1][TOTNUMS]   = nums[1][TOTNUMS-1];
		//nums[2][TOTNUMS-1] = nums[2][TOTNUMS-2];
		//nums[3][TOTNUMS-2] = nums[3][TOTNUMS-3];
         	transferandcalc();
	    }
}

/*
{
subnums();
	    if (done != 1 && notallzeroes == 0) {
		//calculate
	    } 
            if (done != 1 && notallzeroes == 1) {
            }
  
}
*/
      } 
      
      fclose(a);
      printf("****TOT:***** %d\n", tot);
	
}

void subnums() {
	    if (done != 1 && notallzeroes == 1) {
notallzeroes = 0;
                for (int i = 0; i <= TOTNUMS-LEVEL; i++) {
         	    nums[LEVEL][i]  = nums[LEVEL-1][i+1] - nums[LEVEL-1][i]; 
		    if (nums[LEVEL][i] != 0) {notallzeroes = 1;}
	        } LEVEL++; }
}

void transferandcalc() {
		for (int z=LEVEL-3; z >= 0; z--) {
			nums[z][TOTNUMS-z+1] = nums[z][TOTNUMS-z] + nums[z+1][TOTNUMS-z];
		}
		tot += nums[0][6];
		printf("NEXT NUM: %d\n", nums[0][6]);
		getchar();
		done = 1;
}
