#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <deque>

#include <unistd.h>

#define getchar()
using namespace std;

int lenx = 0;
int leny = 0;
int lenz = 0;

int LINE = 1000;

deque <int> player1;
deque <int> player2;
int score(deque<int> pl);
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("2020 Day22 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[LINE];

	int p1 = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		//printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);

		if (strcmp(line1, "Player 1:") == 0) {
			p1 = 1;
			continue;
		} else if (strcmp(line1, "Player 2:") == 0) {
			p1 = 0;
			continue;
		} else if (line1[0] == '\0') {
			continue;
		}

		if (p1 == 1) {
			player1.push_back(atoi(line1));
		} else if (p1 == 0) {
			player2.push_back(atoi(line1));
		}

		leny++;
	}
	//printf("size player1 == %d\n", (int)player1.size());
	//printf("size player2 == %d\n", (int)player2.size());

	int round = 0;
	int x1, x2;
	while (1) {
		if ((int)player1.size() == 0 || (int)player2.size() == 0) { break; }
		x1 = player1.front(); x2 = player2.front();
		if (x1 > x2) {
			player1.pop_front();
			player2.pop_front();
			player1.push_back(x1);
			player1.push_back(x2);
		} else if (x1 < x2) {
			player1.pop_front();
			player2.pop_front();
			player2.push_back(x2);
			player2.push_back(x1);
		} else {
			printf("ERR\n"); exit(0);
		}

		round++;
	}
	//printf("round is %d\n", round);
	if ((int)player1.size() != 0) {
		printf("player1 wins (%d)\n", (int)player1.size());
		printf("**score %d\n", score(player1));
		fflush(stdout); dup2(fd, 1);
		printf("**ans: %d\n", score(player1)); exit(0);
	} else {
		printf("player2 wins (%d)\n", (int)player2.size());
		printf("**score %d\n", score(player2));
		fflush(stdout); dup2(fd, 1);
		printf("**ans: %d\n", score(player2)); exit(0);
	}
}

int score(deque<int> pl) {
	int sc = 0;
	//printf("pl.size() is %d\n", (int)pl.size());
	int size = (int)pl.size();
	for (int i = 0; i < size; i++) {
		int val = pl.back();
		//printf("%d - %d\n", val, i+1);
		sc += (val * (i+1));
		pl.pop_back();
	}
	return sc;
}
