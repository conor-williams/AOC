#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <algorithm>

#include <unistd.h>

#define getchar()
using namespace std;

FILE *a;
long long tot = 0;
struct monkey {
	long int mNum;
	deque <long int> items;
	char op;
	long int val;
	long int divNum;
	long int f;
	long int t;
	long int numItems;
};
struct monkey monkeys[20];
long int numMonkeys = 0;
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
	a = fopen(argv[1], "r"); printf("2022 Day11 part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	long int leny = 0;
	long int lineNum = 0;
	while (1) {
next:
		fgets(line1, 999, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		//line1[strlen(line1)-1] = '\0';	

		long int mNum; char ops[20]; long int divNum; long int m1; long int m2; char starts[50];

		if (line1[0] == '\n') {printf("lineNum@ %ld\n", lineNum); goto next;}

		if (lineNum == 0) {sscanf(line1, "Monkey %ld:", &mNum);
			numMonkeys++;
			monkeys[mNum].numItems = 0;
			monkeys[mNum].mNum = mNum;}
		else if (lineNum == 1) {sscanf(line1, "  Starting items: %[^\n]", starts);
			char *first = strtok(starts, ", ");
			do {
				monkeys[mNum].items.push_back(atoi(first));
			} while ((first = strtok(NULL, ", ")) != NULL); }
		else if (lineNum == 2) {sscanf(line1, "  Operation: new = old %[^\n]", ops);
			monkeys[mNum].op = ops[0];
			char ops2[20];
			long int i;
			for (i = 2; i < (int)strlen(ops); i++) {
				ops2[i-2] = ops[i];

			}
			ops2[i-2] = '\0';
			printf("ops2 is [%s]\n", ops2);
			if (strcmp(ops2, "old") == 0) {monkeys[mNum].val = -1;} else {monkeys[mNum].val = atoi(ops2);}}
		else if (lineNum == 3) {sscanf(line1, "  Test: divisible by %ld", &divNum);
			monkeys[mNum].divNum = divNum;}
		else if (lineNum == 4) {sscanf(line1, "    If true: throw to monkey %ld", &m1);
			monkeys[mNum].t = m1;}
		else if (lineNum == 5) {sscanf(line1, "    If false: throw to monkey %ld", &m2);
			monkeys[mNum].f = m2;}
		lineNum++;
		lineNum = lineNum % 6;

		if (lineNum == 0) {printf("%ld: %ld %ld %ld\n", mNum, divNum, m1, m2);}
		if (lineNum == 0) {
			printf("items: ");
			for (auto iter = monkeys[mNum].items.begin(); iter != monkeys[mNum].items.end(); iter++) {
				printf("%ld ", *iter);
			}
			printf("\n");
			printf("op: %c\n", monkeys[mNum].op);
			printf("val: %ld\n", monkeys[mNum].val);
		}
		/*
		   Monkey 0:
		   Starting items: 79, 98
Operation: new = old * 19
Test: divisible by 23
If true: throw to monkey 2
If false: throw to monkey 3
*/


		leny++;
	}
	fclose(a);

	printf("numMonkeys is %ld\n", numMonkeys); getchar();

	for (long int t = 0; t < 20; t++) {
		for (long int m = 0; m < numMonkeys; m++) {
			long int end = monkeys[m].items.size();
			for (long int k = 0; k < end; k++) {
				monkeys[m].numItems++;
				long int v  =  monkeys[m].items.front();	
				monkeys[m].items.pop_front();
				long int v1;
				if (monkeys[m].val == -1) {v1 = v;} else {v1 = monkeys[m].val;}
				long int ans = 0;
				switch (monkeys[m].op) {
					case('+'): ans = v+v1;
						   break;
					case('*'): ans = v*v1;
						   break;
					case('-'): ans = v-v1;
						   break;
					case('/'): ans = v/v1;
						   break;
					default:
						   printf("ERROR"); exit(0);
				}
				ans /= 3;
				long int ans2 = ans % monkeys[m].divNum;						

				if (ans2 == 0) {
					monkeys[monkeys[m].t].items.push_back(ans);
				} else {
					monkeys[monkeys[m].f].items.push_back(ans);
				}
			}
		}
	}
	long int numItems[numMonkeys+1];
	for (long int i = 0; i < numMonkeys; i++) {
		numItems[i] = monkeys[i].numItems;
	}
	for (long int i = 0; i < numMonkeys; i++) {
		printf("%ld: %ld\n", i, numItems[i]);
	}
	sort(numItems, numItems+numMonkeys);
	printf("****mul %ld * %ld = %ld\n", numItems[numMonkeys-1], numItems[numMonkeys-2], numItems[numMonkeys-1]* numItems[numMonkeys-2]);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %ld\n", numItems[numMonkeys-1]* numItems[numMonkeys-2]);
}

