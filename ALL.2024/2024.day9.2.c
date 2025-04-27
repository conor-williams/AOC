#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <string>
#include <iostream>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 21000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

vector <int> ve;
int lenx, leny;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("		2024 Day 9 Part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	lenx = (int)strlen(line1);
	int block = 0;
	for (int i = 0; i < lenx; i+=2) {
		for (int j = 0; j < line1[i] - 48; j++) {
			ve.push_back(block);
		}	
		if (i+1 != lenx) {
			for (int k = 0; k < line1[i+1]-48; k++) {
				ve.push_back(-1);
			}
		}
		if (block == 3004) {printf("3004: %c: %c\n", line1[i], line1[i+1]); getchar();}
		if (block == 3003) {printf("3005: %c: %c\n", line1[i], line1[i+1]); getchar();}
		block++;
	}
	leny++;
}
fclose(a);
	printf("ve.size: %d\n", (int)ve.size()); //getchar();

	for (int i = 0; i < (int)ve.size(); i++) { printf(" %d ", ve[i]); } printf("\n");
	int blockNum = ve.back();
	printf("blockNum is %d\n", blockNum); getchar();
	for (int b1 = blockNum; b1 >= 0; b1--) {
		int lastBPos;
		int firstBPos;
		int first = 1;
		for (int ll = (int)ve.size()-1; ll >= 0; ll--) {
			if (ve[ll] == b1 && first == 1) {
				first = 0;
				lastBPos = ll;
			}
			if (first == 0 && ve[ll] != b1) {
				firstBPos = ll;
				break;
			}
		}
		int lenB = lastBPos - firstBPos;
		//printf("block: %d -- BPos %d %d\n", b1, firstBPos, lastBPos); getchar();
			
		int sz = (int)ve.size();
		int ff = 0;
again:
		int firstMPos = -10;
		int lastMPos = sz-1;
		first = 1;
		for (; ff < sz; ff++) {
			if (ve[ff] == -1 && first == 1) {
				firstMPos = ff;
				first = 0;
			}
			if (first == 0 && ve[ff] != -1) {
				lastMPos = ff;
				break;
			}
		}
		if (firstMPos == -10) {continue;}
		if (firstBPos < firstMPos) {continue;}
		int lenM = lastMPos - firstMPos;
		//printf("block: %d -- MPos %d %d\n", b1, firstMPos, lastMPos); getchar();

		if (lenM >= lenB) {
			//printf("greater -- swap...\n");
			//swapthem
			ve.erase(ve.begin() + firstBPos+1, ve.begin() + lastBPos+1);
			ve.insert(ve.begin() + firstBPos+1, lenB, -1);
			ve.erase(ve.begin() + firstMPos, ve.begin()+firstMPos+lenB);
			ve.insert(ve.begin() + firstMPos, lenB, b1);
			//printf("just done swap:\n"); for (int i = 0; i < (int)ve.size(); i++) { printf("%d ", ve[i]); } printf("\n");getchar();
			
		} else if (lenM < lenB) {
			if (ff < sz) { /*printf("too small, again\n"); */ goto again; }
		}
		//for (int i = 0; i < (int)ve.size(); i++) { printf("%d ", ve[i]); } printf("\n");
		
	}
		
	unsigned long long ans = 0;
	for (int i = 0; i < (int)ve.size(); i++) {
		//if (ve[i] == -1) {printf("ERRROR\n"); exit(0);}
		if (ve[i] != -1) {
			ans += i * (ve[i]);
		}
		//printf("%d * %d: ans: %llu\n", i, ve[i], ans);
	}
	//getchar(); for (int i = 0; i < (int)ve.size(); i++) { printf("%d ", ve[i]); } printf("\n");
		
	printf("size: %d\n", (int)ve.size());

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", ans);
}
