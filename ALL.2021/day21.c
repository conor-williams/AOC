#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <deque>

using namespace std;

FILE *a;
#define LINE 1000
#define getchar()

/*
Player 1 starting position: 4
Player 2 starting position: 8
*/
int startP1; int startP2;

deque <int> qp1;
deque <int> qp2;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2021 Day 21\n"); fflush(stdout);
        char line1[LINE];

int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	sscanf(line1, "Player 1 starting position: %d", &startP1);
	sscanf(line1, "Player 2 starting position: %d", &startP2);
	leny++;
}
fclose(a);
	printf("%d V %d\n", startP1, startP2); getchar();
	for (int i = startP1; i < startP1+10; i++) {
		int j = i % 10; if (j == 0) {j = 10;}
		qp1.push_back(j);
	}
	for (int i = startP2; i < startP2+10; i++) {
		int j = i % 10; if (j == 0) {j = 10;}
		qp2.push_back(j);
	}
		
	printf("qp1\n");
	for (auto it = qp1.begin(); it != qp1.end(); it++) {
		printf(" %d ", *it);
	}
	printf("\n");

	printf("qp2\n");
	for (auto it = qp2.begin(); it != qp2.end(); it++) {
		printf(" %d ", *it);
	}
	printf("\n");

	int roll1 = 1, roll2 = 2, roll3 = 3;
	int round = 0;
	int amt;
	int scorep1 = 0, scorep2 = 0;
	while (1) {
		amt = (roll1+roll2+roll3)%10;
		printf("amt is %d\n", amt);
		if (round % 2 == 0) {
			int val1;
			if (amt == 0) {
			} else {
				for (int k = 0; k < amt; k++) {
					int v1 = qp1.front();
					qp1.pop_front();
					qp1.push_back(v1);
				}
			}
			val1 = qp1.front();
			scorep1 += val1;
			printf("scorep1 += (front)%d ==> %d\n", val1, scorep1); getchar();
		} else {
			int val2;
			if (amt == 0) {
			} else {
				for (int k = 0; k < amt; k++) {
					int v2 = qp2.front();
					qp2.pop_front();
					qp2.push_back(v2);
				}
			}
			val2 = qp2.front();
			scorep2 += val2;
			printf("scorep2 += (front)%d ==> %d\n", val2, scorep2); getchar();
		}

		roll1+=3; roll2+=3; roll3+=3;
		round+=3;

		if (scorep1 >= 1000 || scorep2 >= 1000) {
			break;
		}
	}
	printf("scorep1: %d scorep2: %d\n", scorep1, scorep2); getchar();
	if (scorep1 >= 1000) {
		printf("**ans %d = (%d * %d)\n", scorep2 * round, scorep2, round);
	} else {
		printf("**ans %d = (%d * %d)\n", scorep1 * round, scorep1, round);
	}
}
