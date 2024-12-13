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

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
int var_len = 0;
void sigfunc(int a) { printf("[[ %d ]]\n", var_len); }
int lenx;
int leny;
deque <string> de;
int TIMES = 25;
int main(int argc, char **argv)
{

        signal(SIGQUIT, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);
	if (argc == 3) {TIMES = atoi(argv[2]);} 

        a = fopen(argv[1], "r"); printf("2024 Day 11 Part 1\n"); fflush(stdout);
	int fd = dup(1); close(1);
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

	int times = 0;
again:
	int pos = 0;
	deque<string> deAns;
	deAns.clear();
	for (auto it = de.begin(); it != de.end(); it++) {
		string bla = *it;
		int len = (*it).length();
		if (bla == "0") {
			deAns.push_back("1");
		} else if (len % 2 == 0) {
			char *rem1;
			string split1 = to_string(strtoull((*it).substr(0, len/2).c_str(), &rem1, 10));
			char *rem2;
			string split2 = to_string(strtoull((*it).substr(len/2, len/2).c_str(), &rem2, 10));
			deAns.push_back(split1);
			deAns.push_back(split2);
/*
			deque <string> de1;
			deque <string> de2;
			copy(de.begin()+0, de.begin()+pos+1, back_inserter(de1));
			copy(de.begin()+pos+1, de.end(), back_inserter(de2));
			de1[pos] = split1;
			de2.insert(de2.begin(), split2);
			de1.insert(de1.end(), de2.begin(), de2.end());
			de=de1;
			//sz++;
			pos++;
*/
		} else {
			printf("here3\n");
			char *rem;
			string b1 = to_string(strtoull((*it).c_str(), &rem, 10) * 2024);
			deAns.push_back(b1);
		}
			
		pos++;
	}
	de = deAns;
	var_len = de.size();
	times++;
	printf("times: %d:\n", times); for (auto elem: de) { printf(" %s ", elem.c_str()); } printf("\n");
	if (times < TIMES) {
		getchar();
		goto again; 
	}
	dup2(fd, 1);
	printf("**ans %d\n", (int)de.size());
}
