#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
/*
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;


struct hash_function
{
size_t operator()(const tuple<int , int , int, int>&x) const
{
unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
}
};

*/



FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

int main(int argc, char **argv)
{
	clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2023 Day 1 Part 1\n"); fflush(stdout);
	char line1[LINE];

	leny = 0;
	unsigned long long tot = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		int len = (int)strlen(line1);
		char left;
		char right;
		for (int y = 0; y < len; y++) {
			if (isdigit(line1[y])) {left = line1[y]; break;}
		}
		for (int y = len-1; y>=0; y--) {
			if (isdigit(line1[y])) {right = line1[y]; break;}
		}
		char combine[10];
		combine[0] = left; combine[1] = right; combine[2] = '\0';
		tot += atoi(combine);
		leny++;
	}
	fclose(a);
	printf("**ans: %llu\n", tot);
}
