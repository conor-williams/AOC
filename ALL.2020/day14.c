#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>

using namespace std;

#define getchar()
int lenx = 0;
int leny = 0;
int LINE = 1000;
map <unsigned long long, unsigned long long> mp;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day14\n"); fflush(stdout);
        char line1[LINE];

	char var_mask[100];
	unsigned long long tot;
while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	//line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);

/*
mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
*/
	if (line1[1] == 'a' && line1[2] == 's') {
		sscanf(line1, "mask = %s", var_mask);
		printf("%s\n", var_mask); getchar();
		if (strlen(var_mask) > 37) {
			printf("ERR\n"); exit(0);
		}
	} else if (line1[1] == 'e' && line1[2] == 'm') {
		unsigned long long memPos, memVal;
		sscanf(line1, "mem[%llu] = %llu", &memPos, &memVal);
		printf("%llu -- %llu\n", memPos, memVal); getchar();
		int binarynum[37] = {0};
		for (int x = 0; memVal > 0; x++) {
			binarynum[x] = memVal % 2;
			memVal = memVal / 2;
		}
		//for (int x = 35; x >= 0; x--) { printf("%c", var_mask[35 - x]); } printf("\n"); getchar();
		for (int x = 35; x >= 0; x--) {
			if (var_mask[35-x] == '0') {
				binarynum[x] = 0;
			} else if (var_mask[35-x] == '1') {
				binarynum[x] = 1;
			}
		}
		unsigned long long deci = 0;
		for (int x = 35; x >= 0; x--) {
			printf("%d", binarynum[x]);
			if (binarynum[x] == 1) {
				deci += pow(2, x);
			}
				
		}
		printf("deci %llu\n", deci);
		mp[memPos] = deci;
	}
	
	leny++;
}
	
	tot = 0;
	for (auto it = mp.begin(); it != mp.end(); it++) {
		printf("it->second is %llu -- it->first is %llu\n", it->second, it->first);
		tot += it->second;
	}
		
	printf("** ans %llu\n", tot);
}


