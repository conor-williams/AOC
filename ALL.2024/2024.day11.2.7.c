#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <deque>
#include <set>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
int var_len = 0;
int lenx;
int leny;
deque <string> de;
int times;
int TIMES = 25;
int ar[10000001][21];
void sigfunc(int a) { printf("[[ times: %d length: %d ]]\n", times, var_len); }
int main(int argc, char **argv)
{

	memset(ar, 0, sizeof(ar));
	signal(SIGQUIT, &sigfunc);
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);
	if (argc == 3) {TIMES = atoi(argv[2]);} 

	a = fopen(argv[1], "r"); printf("2024 Day 11 Part 2\n"); fflush(stdout);
	//int fd = dup(1); close(1);
	char line1[LINE];

	leny = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';

		char *fir = strtok(line1, " \0");
		do {
			de.push_back(fir);
		} while ((fir = strtok(NULL, " \0")) != NULL);
		printf("LINE: %s\n", line1);
		leny++;
	}
	fclose(a);

	times = 0;
	char *rem;
	int len;
	//vec <int> nums;
	set <string> nums;

	int T2 = 3;
	unsigned long long maxV = 0;
	for (int kk = 0; kk < 9500000; kk++) {
		de.clear(); de.push_back(to_string(kk));
		if (kk % 100000 == 0) {printf("kk: %d maxV %llu\n", kk, maxV);}
again:
		deque<string> deAns;
		deAns.clear();

		unsigned long long val1 = 0;
		unsigned long long val2 = 0;
		for (auto it = de.begin(); it != de.end(); it++) {
			string bla = *it;
			if (bla == "0") {
				deAns.push_back("1");
				nums.insert("1");
				val1 = 1;

			} else if ((len = bla.length()) % 2 == 0) {
				string s1;
				deAns.push_back(s1 = to_string(val1 = strtoull((bla).substr(0,     len/2).c_str(),     &rem, 10)));
				nums.insert(s1);	
				string s2;
				deAns.push_back(s2 = to_string(val2 = strtoull((bla).substr(len/2, len/2).c_str(), &rem, 10)));
				nums.insert(s2);
			} else {
				string s1;
				
				deAns.push_back(s1 = to_string(val1 = strtoull((bla).c_str(), &rem, 10) * 2024));
				nums.insert(s1);
				
			}
			if (val1 > maxV) {maxV = val1;} 
			if (val2 > maxV) {maxV = val2;}
		}
		//cout << times << ":(" << line1 << ")" << nums.size() << endl;;
		de = deAns; var_len = de.size();
		times++;
		//printf("times: %d:\n", times); for (auto elem: de) { printf(" %s ", elem.c_str()); } printf("\n");
		ar[kk][times] = var_len;
		if (times < T2) {
			//getchar();
			goto again; 
		}
	}
	printf("maxV: %llu\n", maxV);
	//fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", (int)de.size());
}
