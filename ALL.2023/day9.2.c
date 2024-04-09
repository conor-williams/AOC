#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int nums[1000][1000];
long tot = 0;
int TOTNUMSM1 = 20;
//int TOTNUMSM1 = 5;
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
//	    sscanf(line1, "%d %d %d %d %d %d", &nums[0][5], &nums[0][4], &nums[0][3], &nums[0][2], &nums[0][1], &nums[0][0]);
            printf("line1 %s %d %d\n", line1, nums[0][0], nums[0][5]);
            printf("line1 %s\n", line1);
	    //getchar();
            sscanf(line1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &nums[0][20], &nums[0][19], &nums[0][18], &nums[0][17], &nums[0][16], &nums[0][15], &nums[0][14],
                &nums[0][13], &nums[0][12], &nums[0][11], &nums[0][10], &nums[0][9], &nums[0][8], &nums[0][7],
                &nums[0][6], &nums[0][5], &nums[0][4], &nums[0][3], &nums[0][2], &nums[0][1], &nums[0][0]);
//            sscanf(line1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &nums[0][0], &nums[0][1], &nums[0][2], &nums[0][3], &nums[0][4], &nums[0][5], &nums[0][6],
 //               &nums[0][7], &nums[0][8], &nums[0][9], &nums[0][10], &nums[0][11], &nums[0][12], &nums[0][13],
  //              &nums[0][14], &nums[0][15], &nums[0][16], &nums[0][17], &nums[0][18], &nums[0][19], &nums[0][20]);

//printf("nums[0][0] is %d\n", nums[0][0]); printf("nums[0][1] is %d\n", nums[0][1]); printf("nums[0][2] is %d\n", nums[0][2]); printf("nums[0][3] is %d\n", nums[0][3]); printf("nums[0][4] is %d\n", nums[0][4]); printf("nums[0][5] is %d\n", nums[0][5]);
///////////////////////////////////////////////////////////////////////////////////////////////



notallzeroes = 1; LEVEL = 1;

{ 
	subnums();
///LEVEL NOW 2
printf("nums[1][0] is %d\n", nums[1][0]); printf("nums[1][1] is %d\n", nums[1][1]); printf("nums[1][2] is %d\n", nums[1][2]); printf("nums[1][3] is %d\n", nums[1][3]); printf("nums[1][4] is %d\n", nums[1][4]);

	        if (done != 1 && notallzeroes == 0) {
	            printf("calculating as all zeroes...");
		    // calculate
		    done = 1;
	        }
}

for (int q = 1; q <= TOTNUMSM1-1 ; q++) 
{
            subnums();
	    printf("first: nums[%d][0]: %d -- ", q, nums[q][0]); printf("second: nums[%d][1]: %d -- ", q, nums[q][0]); printf("third: nums[%d][2]: %d\n", q, nums[q][0]);
	    if (done != 1 && notallzeroes == 0) { 

		nums[q][TOTNUMSM1-q+1] = nums[q][TOTNUMSM1-q];
		//nums[1][TOTNUMSM1]   = nums[1][TOTNUMSM1-1];
		//nums[2][TOTNUMSM1-1] = nums[2][TOTNUMSM1-2];
		//nums[3][TOTNUMSM1-2] = nums[3][TOTNUMSM1-3];
         	transferandcalc();
	    }
		if (done == 1) break;
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
      printf("****TOT:***** %ld\n", tot);
	
}

void subnums() {
	    if (done != 1 && notallzeroes == 1) {
notallzeroes = 0;
                for (int i = 0; i <= TOTNUMSM1-LEVEL; i++) {
         	    nums[LEVEL][i]  = nums[LEVEL-1][i+1] - nums[LEVEL-1][i]; 
		    if (nums[LEVEL][i] != 0) {printf("setting notallzeroes... val: %d LEVEL: %d i: %d\n", nums[LEVEL][i], LEVEL, i); notallzeroes = 1;
		        printf("val: %d val2: %d i: %d\n", nums[LEVEL-1][i+1], nums[LEVEL-1][i]);}
	        } 
                LEVEL++;
            }
            if (notallzeroes == 0) {printf("GOT ALL ZEROES...\n");}
              
}

void transferandcalc() {
printf("in transferandcalc...\n");
		for (int z=LEVEL-3; z >= 0; z--) {
			nums[z][TOTNUMSM1-z+1] = nums[z][TOTNUMSM1-z] + nums[z+1][TOTNUMSM1-z];
		}
		tot += nums[0][TOTNUMSM1+1];
		printf("NEXT NUM: %d\n", nums[0][TOTNUMSM1+1]);
		//getchar();
		done = 1;
}
