#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <deque>
#include <assert.h>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx = 0;
int leny = 0;
int lenz = 0;
#define getchar()

int LINE = 1000;

deque <int> deck;
int ROUNDS = 100;
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	if (argc == 3) {ROUNDS = atoi(argv[2]);}
        FILE *a = fopen(argv[1], "r"); printf("2020 Day23 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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
	leny++;
}

	printf("START\n");
	for (auto it = deck.begin(); it != deck.end(); it++) {
		printf(" %d ", *it);
	}
	printf("\n");
	for (int r = 1; r <= ROUNDS; r++) {
		int top = deck.front();
		deck.pop_front();
		int t1 = deck.front();
		deck.pop_front();
		int t2 = deck.front();
		deck.pop_front();
		int t3 = deck.front();
		deck.pop_front();
		deck.push_front(top);
		int origSel = top;
		int sel = top-1;
		if (sel == 0) {sel = 9;}

		printf("sel is %d\n", sel); getchar();
		if (sel != t1 && sel != t2 && sel != t3) {
			printf("here1 sel is fine\n");
			deck.pop_front();
			deck.push_back(top);
			
			do {
				int n1 = deck.front();
				if (n1 == sel) {
					break;
					//ok
				} else if (n1 != sel) {
					deck.pop_front();
					deck.push_back(n1);
				}
				printf("in while... n1:%d sel:%d\n", n1, sel); getchar();
			} while (1);
			int n1_1 = deck.front();
			deck.pop_front();
			deck.push_front(t3);
			deck.push_front(t2);
			deck.push_front(t1);
			deck.push_front(n1_1);
		} else {
			printf("here2 sel not fine\n");
			do {
				sel = sel-1;
				if (sel == 0) {sel = 9;}
			} while (sel == t1 || sel == t2 || sel == t3);
			printf("sel now %d\n", sel);

			int cur;
			while ((cur = deck.back()) != sel) {
				deck.pop_back();
				deck.push_front(cur);
			}
			deck.push_back(t1);
			deck.push_back(t2);
			deck.push_back(t3);
			printf("interim %d\n", r);
			for (auto it = deck.begin(); it != deck.end(); it++) {
				printf(" %d ", *it);
			}
			printf("\n");

		}
		int ne;
		while (origSel != (ne = deck.front())) {
			deck.pop_front();
			deck.push_back(ne);
		}
		int tmp = deck.front();
		deck.pop_front();
		deck.push_back(origSel);
		
		assert(tmp == origSel);

		printf("round %d\n", r);
		for (auto it = deck.begin(); it != deck.end(); it++) {
			printf(" %d ", *it);
		}
		printf("\n");
	}


	printf("**ANS round %d\n", ROUNDS);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: ");
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
	printf("\n");
}
