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
#include <algorithm>
#include <iostream>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
int var_len = 0;
void sigfunc(int a) { printf("[[ %d ]]\n", var_len); }
int lenx;
int leny;
vector <string> ve;
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
		ve.push_back(fir);
	} while ((fir = strtok(NULL, " \0")) != NULL);
        printf("LINE: %s\n", line1);
	leny++;
}
fclose(a);

	int times = 0;
again:
	int sz = ve.size();
	
	printf("here1\n"); fflush(stdout);
	for (int pos = 0; pos < sz; pos++) {
		string bla = ve[pos];
		int len = ve[pos].length();
		if (bla == "0") {
			ve[pos] = "1";
		} else if (len % 2 == 0) {
			char *rem1;
			string split1 = to_string(strtoull(ve[pos].substr(0, len/2).c_str(), &rem1, 10));
			char *rem2;
			string split2 = to_string(strtoull(ve[pos].substr(len/2, len/2).c_str(), &rem2, 10));
			vector <string> ve1;
			vector <string> ve2;
			copy(ve.begin()+0, ve.begin()+pos+1, back_inserter(ve1));
			copy(ve.begin()+pos+1, ve.end(), back_inserter(ve2));
			ve1[pos] = split1;
			ve2.insert(ve2.begin(), split2);
			ve1.insert(ve1.end(), ve2.begin(), ve2.end());
			ve=ve1;
			//sz = ve.size();
			sz++;
			pos++;
		} else {
			char *rem;
			ve[pos] = to_string(strtoull(ve[pos].c_str(), &rem, 10) * 2024);
		}
			
	}
	var_len = sz;
	times++;
	//printf("times: %d:\n", times); for (auto elem: ve) { printf(" %s ", elem.c_str()); } printf("\n");
	if (times < TIMES) {
		getchar();
		goto again; 
	}
	fflush(stdout); dup2(fd, 1);
	printf("**ans %d\n", (int)ve.size());
}
