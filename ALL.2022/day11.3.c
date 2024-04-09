#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <algorithm>

using namespace std;
#define getchar()

FILE *a;
long long tot = 0;
struct monkey {
	long long int mNum;
	deque <long long int> items;
	char op;
	long long int val;
	long long int divNum;
	long long int f;
	long long int t;
	long long int numItems;
	};
struct monkey monkeys[20];
long long int numMonkeys = 0;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);
        a = fopen(argv[1], "r"); printf("2022 Day11 part1\n"); fflush(stdout);
        char line1[1000];

long long int leny = 0;
long long int lineNum = 0;
while (1) {
next:
        fgets(line1, 999, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	//line1[strlen(line1)-1] = '\0';	
	
	long long int mNum; char ops[20]; long long int divNum; long long int m1; long long int m2; char starts[50];

	if (line1[0] == '\n') {printf("lineNum@ %lld\n", lineNum); goto next;}

	if (lineNum == 0) {sscanf(line1, "Monkey %lld:", &mNum);
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
		long long int i;
		for (i = 2; i < (int)strlen(ops); i++) {
			ops2[i-2] = ops[i];
			
		}
		ops2[i-2] = '\0';
		printf("ops2 is [%s]\n", ops2);
		if (strcmp(ops2, "old") == 0) {monkeys[mNum].val = -1;} else {monkeys[mNum].val = atoi(ops2);}}
	else if (lineNum == 3) {sscanf(line1, "  Test: divisible by %lld", &divNum);
		monkeys[mNum].divNum = divNum;}
	else if (lineNum == 4) {sscanf(line1, "    If true: throw to monkey %lld", &m1);
		monkeys[mNum].t = m1;}
	else if (lineNum == 5) {sscanf(line1, "    If false: throw to monkey %lld", &m2);
		monkeys[mNum].f = m2;}
	lineNum++;
	lineNum = lineNum % 6;

	if (lineNum == 0) {printf("%lld: %lld %lld %lld\n", mNum, divNum, m1, m2);}
	if (lineNum == 0) {
		printf("items: ");
		for (auto iter = monkeys[mNum].items.begin(); iter != monkeys[mNum].items.end(); iter++) {
			printf("%lld ", *iter);
		}
		printf("\n");
		printf("op: %c\n", monkeys[mNum].op);
		printf("val: %lld\n", monkeys[mNum].val);
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

printf("numMonkeys is %lld\n", numMonkeys); getchar();

        long long int supermodulo = 1;
        for (int i = 0; i < numMonkeys; i++) {
                supermodulo *= monkeys[i].divNum;
        }

	for (long long int t = 0; t < 10000; t++) {
		for (long long int m = 0; m < numMonkeys; m++) {
			long long int end = monkeys[m].items.size();
			for (long long int k = 0; k < end; k++) {
				monkeys[m].numItems++;
				long long int v  =  monkeys[m].items.front();	
				monkeys[m].items.pop_front();
				long long int v1;
				if (monkeys[m].val == -1) {v1 = v;} else {v1 = monkeys[m].val;}
				long long int ans = 0;
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
				//ans /= 3;
				long long int ans2 = ans % monkeys[m].divNum;						
				ans = ans % supermodulo;
	
				if (ans2 == 0) {
					monkeys[monkeys[m].t].items.push_back(ans);
				} else {
					monkeys[monkeys[m].f].items.push_back(ans);
				}
			}
		}
		int t1 = t+1;
		if ( t1 == 1 || t1== 20 || t1== 999|| t1==1000 || t1 == 2000 || t1==3000 || t1==4000 || t1==5000 
			|| t1 == 6000|| t1==7000 || t1 == 8000 || t1== 9000 || t1==10000) {
			printf("t1 is %d\n", t1);
			long long int numItems[numMonkeys+1];
			for (long long int i = 0; i < numMonkeys; i++) {
				numItems[i] = monkeys[i].numItems;
			}
			for (long long int i = 0; i < numMonkeys; i++) {
				printf("%lld: %lld\n", i, numItems[i]);
			} getchar();
		}
	}
	long long int numItems[numMonkeys+1];
	for (long long int i = 0; i < numMonkeys; i++) {
		numItems[i] = monkeys[i].numItems;
	}
	sort(numItems, numItems+numMonkeys);
	printf("****mul %lld * %lld = %lld\n", numItems[numMonkeys-1], numItems[numMonkeys-2], numItems[numMonkeys-1]*
			numItems[numMonkeys-2]);
	for (long long int i = 0; i < numMonkeys; i++) {
		printf("%lld: %lld\n", i, numItems[i]);
	}
}

