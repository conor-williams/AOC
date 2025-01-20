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
void main(int argc, char **argv)
{
        printf("%d", argc);
        printf("%s", argv[1]);
        fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day7.1\n"); fflush(stdin); fflush(stdout);

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

notallzeroes = 1;
LEVEL = 1;
{ 
subnums();
///LEVEL NOW 2
printf("nums[1][0] is %d\n", nums[1][0]); printf("nums[1][1] is %d\n", nums[1][1]); printf("nums[1][2] is %d\n", nums[1][2]); printf("nums[1][3] is %d\n", nums[1][3]); printf("nums[1][4] is %d\n", nums[1][4]);

	        if (done != 1 && notallzeroes == 0) {
	            printf("calculating as all zeroes...");
nums[0][TOTNUMS+1] = nums[0][TOTNUMS] + nums[1][TOTNUMS];
		    // calculate
		    done = 1;
	        }
}

{
subnums();
	    if (done != 1 && notallzeroes == 0) {    //calculate
//nums[LEVEL-1][TOTNUMS] = nums[LEVEL-1][TOTNUMS-1];
		nums[1][5] = nums[1][4]; 
//		nums[0][6] = nums[0][5] + nums[1][5];
//nums[LEVEL-1][TOTNUMS-LEVEL+2] = nums[LEVEL-1][TOTNUMS-LEVEL+1];
nums[1][TOTNUMS]   = nums[1][TOTNUMS-1];
//nums[0][TOTNUMS+1] = nums[0][TOTNUMS] + nums[1][TOTNUMS];
for (int z=LEVEL-3; z >= 0; z--) {
nums[z][TOTNUMS-z+1] = nums[z][TOTNUMS-z] + nums[z+1][TOTNUMS-z];
}
/*
for (int z=LEVEL-2; z >= 0; z--) {
   nums[z][TOTNUMS+z-1] = nums[z][TOTNUMS+z-2] + nums[z+1][TOTNUMS+z-2];
}
*/
/*
nums[1][TOTNUMS]   = nums[1][TOTNUMS-1];
nums[0][TOTNUMS+1] = nums[0][TOTNUMS] + nums[1][TOTNUMS];
*/
		tot += nums[0][6];
		printf("NEXT NUM: %d\n", nums[0][6]);
		getchar();
		done = 1;
	    } 
}

{
            subnums();
printf("LEVEL is %d\n", LEVEL);
//LEVEL NOW 4
	    if (done != 1 && notallzeroes == 0) {
printf("calculating as all zeroes...");
                nums[2][4] = nums[2][3];
//		nums[1][5] = nums[1][4] + nums[2][4]; 
//		nums[0][6] = nums[0][5] + nums[1][5];
nums[2][TOTNUMS-1] = nums[2][TOTNUMS-2];
for (int z=LEVEL-3; z >= 0; z--) {
nums[z][TOTNUMS-z+1] = nums[z][TOTNUMS-z] + nums[z+1][TOTNUMS-z];
}
//nums[1][TOTNUMS]   = nums[1][TOTNUMS-1] + nums[2][TOTNUMS-1];
//nums[0][TOTNUMS+1] = nums[0][TOTNUMS] + nums[1][TOTNUMS];
		tot += nums[0][6];
printf("NUM %d\n", nums[0][6]);
getchar();
		done = 1;
		//calculate
	    }
}

{//LEVEL NOW 4
subnums();

if (done != 1 && notallzeroes == 0) {
/*
            if (nums[4][0] == 0 && nums[4][1] == 0) 
*/
//		nums[3][3] = nums[3][2];
//              nums[2][4] = nums[2][3] + nums[3][3];
//		nums[1][5] = nums[1][4] + nums[2][4]; 
//		nums[0][6] = nums[0][5] + nums[1][5];

nums[3][TOTNUMS-2] = nums[3][TOTNUMS-3];
for (int z=LEVEL-3; z >= 0; z--) {
nums[z][TOTNUMS-z+1] = nums[z][TOTNUMS-z] + nums[z+1][TOTNUMS-z];
}
//nums[2][TOTNUMS-1] = nums[2][TOTNUMS-2] + nums[3][TOTNUMS-2];
//nums[1][TOTNUMS]   = nums[1][TOTNUMS-1] + nums[2][TOTNUMS-1];
//nums[0][TOTNUMS+1] = nums[0][TOTNUMS] + nums[1][TOTNUMS];
		tot += nums[0][6];
printf("NUMNEW: nums[0][6] %d\n", nums[0][6]);
getchar();
		done = 1;
		//calculate
	    } 
}

{//LEVEL NOW 5
subnums();
	    if (done != 1 && notallzeroes == 0) {
		//calculate
	    } 
            if (done != 1 && notallzeroes == 1) {
            }
  
}
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

