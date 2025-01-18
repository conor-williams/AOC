#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <algorithm>

#include <unistd.h>

#define getchar()
#define assert(asdf)
//#include <iostream>

using namespace std;
FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

vector <int> left;
vector <int> right;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 1 part 2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int a, b;
	sscanf(line1, "%d %d", &a, &b);
	left.push_back(a);
	right.push_back(b);
	leny++;
}
fclose(a);

	//auto it = unique(left.begin(), left.end());
	//left.resize(distance(left.begin(), it));

	printf("left:\n");
	for (auto it2 = left.begin(); it2 != left.end(); it2++) {
		printf("%d ", *it2);
	}
	printf("\n");

	int num = left.size();
	int numR = right.size();
	unsigned long long dist= 0;
	for (int i = 0; i < num; i++) {
		int times = 0;
		int what = left.back();
		for (int j = 0; j < numR; j++) {
			if (right.at(j) == what) {
				times++;
			}
		}
		dist += left.back() * times;
		left.pop_back();
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", dist);
		
}
