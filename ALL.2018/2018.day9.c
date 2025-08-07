#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

#include <unistd.h>

#define getchar()
#undef _DEBUG_
#define SIZE 200
char line1[SIZE];
unsigned long tot = 0;
deque <int> circle;

void play(int players, int lastMarble);
int fd;

void rotateAnti(int d);
void rotateAnti(int d)
{
    for (int i = 0; i < d; i++) {
        int val = circle.front();
        circle.pop_front();
        circle.push_back(val);
    }
    // Print the rotated array
    //for (auto ii: circle) { cout << " " << ii; }
    //cout << endl;
}
void rotateClock(int d);
void rotateClock(int d)
{
    for (int i = 0; i < d; i++) {
        int val = circle.back();
        circle.pop_back();
        circle.push_front(val);
    }
    // Print the rotated array
    //for (auto ii: circle) { cout << " " << ii; }
    //cout << endl;
}
int main(int argc, char **argv)
{
	///rintf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("		2018 Day9.1\n"); fflush(stdout);

	fflush(stdout); fd = dup(1); close(1);
	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		int players, lastMarble;
		sscanf(line1, "%d players; last marble is worth %d points", &players, &lastMarble);
		printf("players: %d lastMarble: %d\n", players, lastMarble);
		getchar();
		play(players, lastMarble); leny++;
	}
	fclose(a);

	//printf("**tot %lu\n", tot);
}

void play(int players, int lastMarble) {
	//circle[0] = 0;
	//circle[0] = 2;
	//circle[1] = 1; //len2 //player2
	//circle[2] = 3; //len3 //player2
	circle.clear();

	circle.push_back(2);
	circle.push_back(1);
	circle.push_back(3);
	circle.push_back(0);
	circle.push_back(4);

	unsigned long long score[1000] = {0};
	int origI = 4;
	while (1) {
		origI++;
		if (origI > lastMarble) {break;}

		int pl = origI % players;
		if ((origI % 23) != 0) {
			rotateAnti(1);
			circle.push_back(origI);
		} else {
			rotateClock(7);
			rotateClock(1);
			int val = circle.front();
			circle.pop_front();
			rotateAnti(1);
			score[pl] += (origI) + val;
		//	printf("origI: %d val: %d\n", origI, val);

		}

	} 
	unsigned long long max = 0;
	for (int s = 0; s < players; s++) {
		if (score[s] > max) {max = score[s];}
	}

	printf("MAX SCORE %llu\n", max);
	fflush(stdout); dup2(fd, 1);
	printf("*ans: %llu\n", max);
}
