#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <deque>
#include <map>
#include <set>
#include <vector>
#include <array>

using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
int lenx;
int leny;
deque <unsigned long long> secrets;
int TIMES = 2000;
void printit(deque <unsigned long long> s1);
unsigned long long mix(unsigned long long secret, unsigned long long in);
unsigned long long prune(unsigned long long in);

array <map <tuple<int, int, int, int>, int>, 3000> sequence;
set <tuple<int, int, int, int>> seqset;
deque <tuple<int, int, int, int>> seqQ;
tuple<int, int, int, int> maxtu;

struct diff_s {
	int val;
	int dif;
};
unsigned long long maxSum = 0;
int curTot = 0;
int curInQ = 0;
void sigfunc(int a) { printf("[[ %d of %d ]]\n", curInQ, curTot); }
struct diff_s diffs[3000][2001];
int main(int argc, char **argv)
{
	if (argc == 3) {TIMES = atoi(argv[2]);}

        //signal(SIGTSTP, &sigfunc);
        signal(SIGQUIT, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 22 Part 2\n"); fflush(stdout);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	char *bla;
	unsigned long long pu = strtoull(line1, &bla, 10);
	secrets.push_back(pu);
	leny++;
}
fclose(a);
	for (int i = 0; i < TIMES; i++) {
		deque <unsigned long long> secretsTmp;
		int numpos = 0;
		for (auto snum: secrets) {
			unsigned long long snumBef = snum;
			unsigned long long mul1 = snum *64;
			snum = mix(snum, mul1);
			snum = prune(snum);
			unsigned long long div1 = snum / 32;
			snum = mix(snum, div1);
			snum = prune(snum);
			unsigned long long mul2 = snum * 2048;
			snum = mix(snum, mul2);
			snum = prune(snum);
			secretsTmp.push_back(snum);
			
			diffs[numpos][i].dif = (snum % 10 - snumBef % 10);
			diffs[numpos][i].val = (snum % 10);
			numpos++;
		}
		
		secrets = secretsTmp;
		secretsTmp.clear();		
	}
	//printit(secrets);
	//unsigned long long sum = 0; //for (auto one: secrets) { sum += one; }
/*
	for (int numpos = 0; numpos < leny; numpos++) { 
		for (int i = 0; i < TIMES; i++) { 
			//printf("%d: %d %d\n", numpos, diffs[numpos][i].val, diffs[numpos][i].dif); 
		}
	}
*/
	printf("Creating Sequences + seqset + seqQ\n");
	int curCreate = 0;
	for (int numpos = 0; numpos < leny; numpos++) {
		if (curCreate % 300 == 0) {printf("	(%4d) of (%d)\n", curCreate, leny);}
		
		diff_s *diffsPtr = diffs[numpos];
		curCreate++;
		for (int i = 3; i < TIMES; i++) {
			int one = diffsPtr[i-3].dif;
			int two = diffsPtr[i-2].dif;
			int three = diffsPtr[i-1].dif;
			int four = diffsPtr[i].dif;
			tuple <int, int, int, int> tu1 = make_tuple(one, two, three, four);
			int v5 = diffsPtr[i].val;

			if (sequence[numpos].find(tu1) == sequence[numpos].end()) {
				sequence[numpos][tu1] = v5;
				if (seqset.find(tu1) == seqset.end()) {
					seqset.insert(tu1);
					seqQ.push_back(tu1);
				}
			} else {
			}
		}
	}

	printf("Created Sequences + seqset + seqQ\n");
	curTot = 0;
	printf("seqQ size is %d\n", curTot = (int)seqQ.size());
	curInQ = 0;
	printf("Summing each in seqQ\n");
	///defref of a array is slow... (todo...!)
	unsigned long long tmpSum = 0;
	for (auto tu: seqQ) {
		if (curInQ % 3000 == 0) {printf("	(%5d) of (%d)\n", curInQ, curTot);}
		curInQ++;
		tmpSum = 0;
		for (int numpos = 0; numpos < leny; numpos++) {
			//look ahead
			if ((((leny - numpos) * 9) + tmpSum) < maxSum) {goto next;}
			if (sequence[numpos].find({tu}) != sequence[numpos].end()) {
				//assert(sequence[numpos][{tu}] < 10 && sequence[numpos][{tu}] >= 0);
				tmpSum += sequence[numpos][{tu}];
			}
		}
		if (tmpSum > maxSum) {maxtu = tu; maxSum = tmpSum;}
next:
		continue;
	}
	printf("maxtu %d,%d,%d,%d\n", get<0>(maxtu), get<1>(maxtu), get<2>(maxtu), get<3>(maxtu));
	printf("TIMES: %d\n", TIMES);
	printf("**ans %llu\n", maxSum);
		
}
void printit(deque <unsigned long long> s1) {
	for (auto n1: s1) {
		printf("%llu " , n1);
	}
	printf("\n");
}
unsigned long long mix(unsigned long long secret, unsigned long long inin) {
	return inin ^ secret;
	
}
unsigned long long prune(unsigned long long inin) {
	return inin % 16777216;
}














/* -- 
	maxSum = 0; tuple <int, int, int, int> my_var = make_tuple(0, 0, -1, 1);

	int myvarSum = 0;
	for (int numpos = 0; numpos < leny; numpos++) {
		if (sequence[numpos].find({my_var}) != sequence[numpos].end()) {
			myvarSum += sequence[numpos][{my_var}];
		}
	}
	printf("myvarSum is %d\n", myvarSum);
*/
			//int one = get<0>(tu.first);
			//int two = get<1>(tu.first);
			//int three = get<2>(tu.first);
			//int four = get<3>(tu.first);
			//printf("%d %d %d %d -> %d\n", one, two, three, four, tu.second);
/*
	printf("Creating seqset\n");
	int seqCreate = 0;
	for (int numpos = 0; numpos < leny; numpos++) {
		seqCreate++;
		if (seqCreate % 300 == 0) {printf("(%d) of (%d)\n", seqCreate, leny);}
		
		for (auto elem: sequence[numpos]) {
			if (seqset.find(elem.first) == seqset.end()) {
				seqset.insert(elem.first);
			}
		}
	}
	printf("Created seqset\n");
*/
/*
				if (v5 > sequence[numpos][{one, two, three, four}]) {
					//only the first time -- not the largest
					//sequence[numpos][{one, two, three, four}] = v5;
				}
*/
/*
			int one = diffs[numpos][i-3].dif;
			int two = diffs[numpos][i-2].dif;
			int three = diffs[numpos][i-1].dif;
			int four = diffs[numpos][i].dif;
			tuple <int, int, int, int> tu1 = make_tuple(one, two, three, four);
			int v5 = diffs[numpos][i].val;
*/
