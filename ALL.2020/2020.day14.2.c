#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <map>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

#define getchar()
int lenx = 0;
int leny = 0;
int LINE = 1000;
map <unsigned long long, unsigned long long> mp;
void genBinOne(int n, int zeroes, char *mask, int *poses);
int main(int argc, char **argv)
{
	FILE *a = fopen(argv[1], "r"); printf("		2020 Day14 Part2\n"); fflush(stdout);
	char line1[LINE];

	fflush(stdout); int fd = dup(1); close(1);
	/*
	string xx = string(10, '3');
	cout << xx << endl;
	exit(0);
	*/
	char var_mask[100];
	char var_maskOrig[100];
	unsigned long long tot;
	int numX = 0;
	int numXOrig = 0;
	int posesX[200];
	int posesXOrig[200];

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
			numX = 0;
			sscanf(line1, "mask = %s", var_mask);
			printf("here1... %s\n", var_mask);
			strcpy(var_maskOrig, var_mask);
			for (int ii = (int)strlen(var_mask)-1; ii>=0; ii--) {
				if (var_mask[ii] == 'X') {
					posesX[numX] = ii;
					posesXOrig[numX] = ii;
					numX++;
				}
			}
			numXOrig = numX;
			
			printf("%s\n", var_mask); getchar();
			if (strlen(var_mask) > 37) {
				printf("ERR\n"); exit(0);
			}
		} else if (line1[1] == 'e' && line1[2] == 'm') {
			numX = numXOrig;
			for (int i = 0; i < 36; i++) {
				posesX[i] = posesXOrig[i];
			}
			strcpy(var_mask, var_maskOrig);

			unsigned long long memPos, memVal;
			sscanf(line1, "mem[%llu] = %llu", &memPos, &memVal);
			unsigned long long memValOrig = memVal;
			printf("%llu -- %llu\n", memPos, memVal); getchar();
			
			{
				int binarynum_mempos[37] = {0};
				for (int x = 0; memPos > 0; x++) {
					binarynum_mempos[35-x] = memPos % 2;
					memPos = memPos / 2;
				}
				printf("mempos now in binary:\n");
				for (int x = 35; x >= 0; x--) { printf("%d", binarynum_mempos[35 - x]); } printf("\n"); getchar();
				for (int x = 0; x < (int)strlen(var_mask); x++) {
					if (var_mask[x] == 'X') {
					} else if (var_mask[x] == '1' 
							|| binarynum_mempos[x] == 1) {
						var_mask[x] = '1';
					}
				}
			}

			/*
			int binarynum[37] = {0};
			int binarynumOrig[37] = {0};
			for (int x = 0; memVal > 0; x++) {
				binarynum[x] = memVal % 2;
				binarynumOrig[x] = memVal % 2;
				memVal = memVal / 2;
			}
			*/
			printf("memValOrig: %llu\n", memValOrig);
			//for (int x = 35; x >= 0; x--) { printf("%c", binarynum[35 - x]); } printf("\n"); getchar();
			for (int kk = 0; kk < pow(2, numX); kk++) { 
				/*
				for (int ij = 0; ij < 35; ij++) {
					binarynum[ij] = binarynumOrig[ij];
				}
				*/
				printf("var_mask was %s\n", var_mask);
				genBinOne(kk, numX, var_mask, posesX);
				printf("var_mask is %s\n", var_mask); getchar();
				/*
				for (int x = 35; x >= 0; x--) {
					if (var_mask[35-x] == '0') {
						binarynum[x] = 0;
					} else if (var_mask[35-x] == '1') {
						binarynum[x] = 1;
					}
				}
				*/
				unsigned long long deci = 0;
				for (int x = 35; x >= 0; x--) {
					printf("%d", var_mask[35-x]);
					if (var_mask[35-x] == '1') {
						deci += pow(2, x);
					}

				}
				printf("deci %llu\n", deci);
				mp[deci] = memValOrig;
			}
		}

		leny++;
	}

	tot = 0;
	for (auto it = mp.begin(); it != mp.end(); it++) {
		printf("it->first is %llu -- it->second is %llu\n", it->first, it->second);
		tot += it->second;
	}

	fflush(stdout); dup2(fd, 1);
	printf("** ans %llu\n", tot);
	fflush(stdout);
}

void genBinOne(int n, int zeroes, char *mask, int *poses) {
    
        string s = string(zeroes, '0');
        
        // Get Binary Representation of i
	int zer = zeroes-1;
        for (int xx = n; xx; xx >>= 1) {
        	s[zer--] = xx & 1 ? '1' : '0';
	}
	for (int ii = 0; ii < zeroes; ii++) {
		mask[poses[ii]] = s[ii];
	}
}

void genBin(int n) {//geekforgeeks.org
    
    for (int i = 1; i <= n; i++) {
        string s;
        
        // Get Binary Representation of i
        for (int x = i; x; x >>= 1)
            s = (x & 1 ? "1" : "0") + s;
            
        cout << s << endl;
    }
}
