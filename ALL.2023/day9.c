#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int nums[1000][30];
void main(int argc, char **argv)
{
        printf("%d", argc);
        printf("%s", argv[1]);
        fflush(stdin); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day7.1\n"); fflush(stdin); fflush(stdout);

        char line1[1000];
long tot = 0;
        while (1) {
	    int done = 0;
            fgets(line1, 1000, a); if (feof(a)) {break;}
	    sscanf(line1, "%d %d %d %d %d %d", &nums[0][0], &nums[0][1], &nums[0][2], &nums[0][3], &nums[0][4], &nums[0][5]);
/*
	    sscanf(line1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &nums[0][0], &nums[0][1], &nums[0][2], &nums[0][3], &nums[0][4], &nums[0][5], &nums[0][6],
	    	&nums[0][7], &nums[0][8], &nums[0][9], &nums[0][10], &nums[0][11], &nums[0][12], &nums[0][13],
	    	&nums[0][14], &nums[0][15], &nums[0][16], &nums[0][17], &nums[0][18], &nums[0][19], &nums[0][20]);
*/
            printf("line1 %s %d %d\n", line1, nums[0][0], nums[0][5]);
	    getchar();

		
            for (int k = 0; k <= 20; k++) {
	            for (int i = 0; i <= 19 - k; i++) {
       		  	    nums[k+1][i]  = nums[k][i+1] - nums[k][i]; 
       		    } 
		    for (int i = 0; i<= 19 -k; i++) {
			if (nums[k+1][i] == 0) {
			} else {
			   foundnonzero = 1;
			}
		    }
	    }
/*
				//calculate
				nums[k][i] = nums[k][i-1];
				for (int l = k-1; l => 0; l--) {
				    nums[l][i-1] = nums[l][i-2] + nums[k][i];
				    NUM = nums[l][i-2];
			        }	
			}
		    }
*/
            }

            if (nums[1][0] == 0 && nums[1][1] == 0 && nums[1][2] == 0 && nums[1][3] == 0 
			&& nums[1][4] == 0) {
		// calculate
	    } else {
	        nums[2][0]  = nums[1][1] - nums[1][0]; 
	        nums[2][1]  = nums[1][2] - nums[1][1]; 
	        nums[2][2]  = nums[1][3] - nums[1][2]; 
	        nums[2][3]  = nums[1][4] - nums[1][3]; 
            }
	    printf("nums[2][3]: %d\n", nums[2][3]);


            if (nums[2][0] == 0 && nums[2][1] == 0 && nums[2][2] == 0 && nums[2][3] == 0) {
	        //calculate
		nums[1][5] = nums[1][4]; 
		nums[0][6] = nums[0][5] + nums[1][5];
done = 1;
		tot += nums[0][6];
		printf("NEXT NUM: %d\n", nums[0][6]);
		getchar();
	    } else {
	        nums[3][0]  = nums[2][1] - nums[2][0]; 
	        nums[3][1]  = nums[2][2] - nums[2][1]; 
	        nums[3][2]  = nums[2][3] - nums[2][2]; 

	    }

            if (done == 0 && nums[3][0] == 0 && nums[3][1] == 0 && nums[3][2] == 0) {
                nums[2][4] = nums[2][3];
		nums[1][5] = nums[1][4] + nums[2][3]; 
		nums[0][6] = nums[0][5] + nums[1][5];
done = 1;
		tot += nums[0][6];
printf("NUM %d\n", nums[0][6]);
getchar();
		//calculate
	    } else {
	        nums[4][0]  = nums[3][1] - nums[3][0]; 
	        nums[4][1]  = nums[3][2] - nums[3][1]; 
	    }
            if (done == 0 && nums[4][0] == 0 && nums[4][1] == 0) {
		nums[3][3] = nums[3][2];
                nums[2][4] = nums[2][3] + nums[3][3];
		nums[1][5] = nums[1][4] + nums[2][4]; 
		nums[0][6] = nums[0][5] + nums[1][5];
done = 1;
		tot += nums[0][6];
printf("NUMNEW: nums[0][6] %d\n", nums[0][6]);
getchar();
		//calculate
	    } else {
	        nums[5][0]  = nums[4][1] - nums[4][0]; 
	    }

            if (nums[5][0] == 0) {
		//calculate
	    } else {
	    }

      } 
      
      fclose(a);
      printf("****TOT:***** %d\n", tot);
	
}

