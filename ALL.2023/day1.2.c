#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;
void ReplaceString(string &subject, const string search, const string replace);


struct hash_function
{
size_t operator()(const tuple<int , int , int, int>&x) const
{
unsigned int hash = get<0>(x); hash *= 37; hash += get<1>(x); hash *= 27; hash += get<2>(x); hash *= 27; hash += get<3>(x); return hash;
}
};




FILE *a;
#define LINE 2000
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
	printf("        time: %f seconds\n", cpu_time_used);

	//signal(SIGTSTP, &sigfunc);
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("2023 Day 1 Part 2\n"); fflush(stdout);
	char line1[LINE];

	leny = 0;
	unsigned long long tot = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		string l1 = line1;
		//cout << l1 << endl; fflush(stdout);
		ReplaceString(l1, "one", "o1ne");
		ReplaceString(l1, "two", "tw2o");
		ReplaceString(l1, "three", "th3ree");
		ReplaceString(l1, "four", "fo4ur");
		ReplaceString(l1, "five", "fi5ve");
		ReplaceString(l1, "six", "si6x");
		ReplaceString(l1, "seven", "se7ven");
		ReplaceString(l1, "eight", "ei8ght");
		ReplaceString(l1, "nine", "ni9ne");

		strcpy(line1, l1.c_str());
			
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
		//printf("combine: %s\n", combine);
		tot += atoi(combine);
		leny++;
	}
	fclose(a);
	printf("**ans: %llu\n", tot);
}

void ReplaceString(string &subject, const string search, const string replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    //return subject;
}
