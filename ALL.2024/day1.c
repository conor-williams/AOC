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

        a = fopen(argv[1], "r"); printf("2024 Day 1 part 1\n"); fflush(stdout);
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

	sort(left.begin(), left.end());
	sort(right.begin(), right.end());

	int num = left.size();
	unsigned long long dist= 0;
	for (int i = 0; i < num; i++) {
		dist += abs(left.back() - right.back());
		left.pop_back(); right.pop_back();
	}
	assert(right.size() == 0);
	printf("**ans %llu\n", dist);
		
}
