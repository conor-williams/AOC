#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <sys/time.h>
#include <map>

using namespace std;
int lenx = 0;
int leny = 0;
int LINE = 1000;
#define getchar()
//map <int, int> birthTime;
//map <int, bool> hasKey;
#define END 30000000
int birthTime[END+1];
bool hasKey[END+1] = {false};
int lastNumber, nextNumber;
int main(int argc, char **argv)
{

	FILE *a = fopen(argv[1], "r"); printf("2020 Day15 Part2\n"); fflush(stdout);
	int fd = dup(1); close(1);
	char line1[LINE];

	vector <int> nums;
	int starts = 0;
	//0,3,6
	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;

		char *Snum = strtok(line1, ",\n");
		do {
			nums.push_back(atoi(Snum));
			starts++;
		} while ((Snum = strtok(NULL, ",\n")) != NULL);
		leny++;
	}

	//int cstart = clock(); int cend = clock();
	for (int i = 0; i < END ; i++) {
		if (i < starts) {
			nextNumber = nums[i];
		} else {
			if (!hasKey[lastNumber]) {
				nextNumber = 0;
			} else {
				nextNumber = i - birthTime[lastNumber];
			}
		}

		if (i != 0)  {
			birthTime[lastNumber] = i;
			hasKey[lastNumber] = true;
		}
		lastNumber = nextNumber;
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", lastNumber);
}
//
//ta G_Lasso from planet nim -- google_S: solutions 2020 day15 advent of code

/*
   for (int j = 0; j < i-1; j++) {
//printf("nums[j] V nums[i] %d V %d\n", nums[j], nums[i-1]);
if (nums[j] == nums[i-1]) {

found = 1;
//printf("found at pos j %d (%d)\n", j, nums[i-1]);
break;
} 
}
*/
//for (int qq = 0; qq < i+2; qq++) { printf(" %d ", nums[qq]); } printf("\n");
//for (auto iii : nums) { printf(" %d ", iii); } printf("\n");

//#define assert(asf)
/*
   int pos1 = -1, pos2 = -1;
   for (int k = i-1; k >= 0; k--) {
   if (nums[k] == nums[i-1] && pos1 == -1) {
   pos1 = k;
   } else if (nums[k] == nums[i-1] && pos2 == -1) {
   pos2 = k;
   break;
   }
   }
   assert(pos1 != -1);
   assert(pos2 != -1);
   printf("pos1 V i-1 :: %d V %d\n", pos1, i-1);
   assert(pos1 == i-1);
   printf("pos2 V position:: %d V %d\n", pos2, position);
   assert(pos2 == position);
   nums[i] = pos1 - pos2;
   */
