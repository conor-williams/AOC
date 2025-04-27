#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <deque>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>

using namespace std;

int lenx = 0;
int leny = 0;
int lenz = 0;
#define getchar()

int LINE = 1000;
#define assert(asdf)

vector <int> deck;
int ROUNDS = 10000000;
//int ROUNDS = 10;
int fd;
//#define NUMC 9
#define NUMC 1000000
int nextval[NUMC];

int main(int argc, char **argv)
{
//	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	if (argc == 3) {ROUNDS = atoi(argv[2]);}
	FILE *a = fopen(argv[1], "r"); printf("		2020 Day23 Part2\n");
	printf("	SLOW ~1min20seconds\n"); fflush(stdout);
	fd = dup(1); close(1);
	char line1[LINE];

	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);

		for (int i = 0; i < 9; i++) {
			deck.push_back(line1[i]-48);
		}
		for (int i = 9; i <= NUMC; i++) {
			deck.push_back(i+1);
		}
		leny++;
	}
	
	for (int i = 0; i < NUMC-1; i++) {
		nextval[deck[i]] = deck[i+1];
		if (i < 12) {
			printf("nextval %d is %d\n", deck[i], deck[i+1]);
		}
	}
	nextval[deck[NUMC-1]] = deck[0];
	printf("---\n");
	printf("nextval %d is %d\n", deck[NUMC-1], deck[0]);
	getchar();
	

	printf("START\n");
	//for (auto it = deck.begin(); it != deck.end(); it++) { printf(" %d ", *it); } printf("\n");
	//clock_t start, end;
	//start = clock();
	int cur = deck[0];
	for (int r = 1; r <= ROUNDS; r++) {
		//if (r % 10000 == 0) {fflush(stdout); dup2(fd, 1); end = clock();printf("round: %d time: %f\n", r, ((double)(end-start))/CLOCKS_PER_SEC); start=clock(); close(1);}
		int one = nextval[cur];
		int two = nextval[one];
		int three = nextval[two];
		int nthree = nextval[three];
		printf("nthree is %d\n", nthree);
		getchar();
		int dest = cur;
		do {
			dest--;
			if (dest == 0) {dest = NUMC;}
		} while (dest == one || dest == two || dest == three);
		printf("%d %d %d - dest: %d\n", one, two, three, dest);
		getchar();

		int was = nextval[dest];
		nextval[cur] = nthree;
		printf("nextval[%d] is %d\n", cur, nthree);
		nextval[dest] = one;
		printf("nextval[%d] is %d\n", dest, one);
		nextval[three] = was;
		printf("nextval[%d] is %d\n", three, was);
		cur = nthree;
		printf("cur is dest %d %d\n", cur, dest);
		//fflush(stdout); dup2(fd, 1); printf("%d * %d\n", nextval[1], nextval[nextval[1]]); close(1);
	}

	//printf("**ANS round %d\n", ROUNDS);


	printf("%d * %d\n", nextval[1], nextval[nextval[1]]);
	fflush(stdout); dup2(fd, 1);
	unsigned long long ans123 = (unsigned long long)nextval[1] * (unsigned long long)nextval[nextval[1]];
	printf("**ans: %llu\n", ans123);
	fflush(stdout);


	/*
	{
		do {

			int fro = deck.front();
			if (fro == 1) {
				deck.pop_front();
				for (auto it = deck.begin(); it != deck.end(); it++) {
					printf("%d", *it);
				}
				break;
			} else {
				int tmp1 = deck.front();
				deck.pop_front();
				deck.push_back(tmp1);
			}
		} while (1);
	}
	*/
}
