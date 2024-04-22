#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <unistd.h>
#include <deque>

using namespace std;

deque<int> b1;
deque<int> b2;
int lenx, leny;
#define DAY "2016 day16 part1 \n"
#define _DEBUG_
long tot;
#define SIZE 200
#define CDISK 35651584
//#define CDISK 272
#define getchar()
	
int main(int argc, char **argv)
{
	tot = 0;lenx = 0; leny = 0;
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        FILE * a = fopen(argv[1], "r"); 
	printf(DAY); fflush(stdin); fflush(stdout);
       
        char line1[SIZE];
	//int fd = dup(1); close(1);
while(1) 
{
        fgets(line1, SIZE-1, a);
        if (feof(a)) break;
	line1[strlen(line1) -1]='\0';
#ifdef _DEBUG_
//	printf("LINE: %s\n", line1);
#endif
	deque <int> in;
	for (int i = 0; i < (int)strlen(line1); i++) {
		if (line1[i] == '1') {
			in.push_back(1);
		} else {
			in.push_back(0);
		}
	}
	
	int fd = dup(1);
	close(1);
	b1 = in;	
	do {
		printf("in while %d\n", in.size());
		b1.push_back(0);
		for (auto it = in.rbegin(); it != in.rend(); it++)  {
			if (*it == 0) {
				b1.push_back(1);
			} else {
				b1.push_back(0);
			}
		}
		in = b1;
		for (auto it = in.begin(); it != in.end(); it++)  {
			printf("%d", *it);
		}
		printf("\n"); getchar();
	} while (b1.size() < CDISK);

	printf("after while %d\n", in.size());
	while (b1.size() > CDISK) {b1.pop_back();}
	printf("20:\n");
	for (auto it = b1.begin(); it != b1.end(); it++)  {
		printf("%d", *it);
	}

	printf(" here1 (%s) b1.size() is %d\n", line1, (int)b1.size()); getchar();
again:
	b2.clear();
	int sz = (int)b1.size();
	for (int i = 0; i < sz; i++) {
		int c1 = b1.front(); b1.pop_front();
		int c2 = b1.front(); b1.pop_front();
		b2.push_back(c1 == c2);
		i++;
	}
	b1 = b2;
	printf("b1.size is %d\n", (int)b1.size());
	printf("b2.size is %d\n", (int)b1.size());
	if ((b1.size() % 2) == 0) {
		printf("agagin "); getchar();
		goto again;
	} else {
		printf("odd...\n"); getchar();
	}

	dup2(fd, 1);
	printf("ANSWER: ");
	for (auto it = b1.begin(); it < b1.end(); it++) {
		printf("%d", *it);
	}
	printf("\n");
	leny++;
	
}
fclose(a);
		
	printf(" ***tot %ld END\n", tot); fflush(stdout);
} 

