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
void sigfunc(int a) { printf("[[ times: %d length: %d ]]\n", times, var_len); }
int main(int argc, char **argv)
{

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
	set <string> numsPrev;
	set <string> difference;
again:
	numsPrev = nums;

	deque<string> deAns;
	deAns.clear();
	
	for (auto it = de.begin(); it != de.end(); it++) {
		string bla = *it;
		if (bla == "0") {
			deAns.push_back("1");
			nums.insert("1");
			
		} else if ((len = bla.length()) % 2 == 0) {
			string s1;
			deAns.push_back(s1 = to_string(strtoull((bla).substr(0,     len/2).c_str(),     &rem, 10)));
			nums.insert(s1);	
			string s2;
			deAns.push_back(s2 = to_string(strtoull((bla).substr(len/2, len/2).c_str(), &rem, 10)));
			nums.insert(s2);
		} else {
			string s1;
			deAns.push_back(s1 = to_string(strtoull((bla).c_str(), &rem, 10) * 2024));
			nums.insert(s1);
		}
	}
	difference.clear();
	set_difference(nums.begin(), nums.end(), numsPrev.begin(), numsPrev.end(), inserter(difference, difference.begin()));
	deAns.clear();
	
	for (auto it = difference.begin(); it != difference.end(); it++) {
		deAns.push_back(*it);
	}
	cout << times << ":(" << line1 << ")" << nums.size() << endl;;
	de = deAns; var_len = de.size();
	times++;
	//printf("times: %d:\n", times); for (auto elem: de) { printf(" %s ", elem.c_str()); } printf("\n");
	if (times < TIMES) {
		//getchar();
		goto again; 
	}
	//fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", (int)de.size());
}
