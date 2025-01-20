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
#define getchar()
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
	printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2017 Day 3 Part 1\n"); fflush(stdout);
	//fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		char *bla;
		unsigned long long wat = strtoull(line1, &bla, 10);
		unsigned long long sqrt1 = sqrt(wat);
		if (sqrt1 % 2 == 0) {sqrt1--;}
		int x1, y1;
		unsigned long long diff1 = wat - pow(sqrt1, 2);
		if (diff1 == 0) {
			x1 = sqrt1 - 1; y1 = 0;
		} else {
			int quadrant = diff1 / ((sqrt1/2)+1);
			//printf("quadrant is %d\n", quadrant);
			int modval = diff1 % (sqrt1+1);

			if (quadrant == 1 || quadrant == 2 || quadrant == 4 || quadrant == 7) {
				//positive 
				y1 = modval - ((sqrt1/2)+1);
				x1 = (sqrt1/2)+1;
			} else {
				y1 = ((sqrt1/2)+1) - modval;
				x1 = (sqrt1/2)+1;
			}
		}

		//fflush(stdout); dup2(fd, 1);
		printf("man: %d\n", abs(x1) + abs(y1));
		//fflush(stdout); close(1);
		leny++;
	}
	fclose(a);

}
