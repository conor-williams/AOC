#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <deque>
#include <algorithm>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

deque <int> circle2;
#undef _DEBUG_
#define SIZE 40000
char line1[SIZE];
unsigned long tot = 0;
void play(int players, int lastMarble);
#define cSIZE 8000000

void rotateClock(int d);
void rotateClock(int d) 
{ 
    for (int i = 0; i < d; i++) { 
        int val = circle2.front(); 
        circle2.pop_front(); 
        circle2.push_back(val); 
    } 
}
void rotate(int d);
void rotate(int d) 
{ 
    // Push first d elements 
    // from last to the beginning 
    for (int i = 0; i < d; i++) { 
        int val = circle2.back(); 
        circle2.pop_back(); 
        circle2.push_front(val); 
    } 
} 
int main(int argc, char **argv)
{
	printf("%d", argc); printf("@%s", argv[1]); fflush(stdout);
	FILE * a = fopen(argv[1], "r"); printf("2018 Day9.1\n"); fflush(stdout);

	int leny = 0;
	while (1)
	{
		fgets(line1, SIZE-1, a);
		if (feof(a)) break;
		//printf("line1 %s\n", line1);
		line1[strlen(line1)-1] = '\0';
		int players, lastMarble;
		sscanf(line1, "%d players; last marble is worth %d points", &players, &lastMarble);
		printf("players: %d lastMarble: %d\n", players, lastMarble);
		play(players, lastMarble);
		leny++;
	}
	fclose(a);
	printf("**tot %lu\n", tot);
}

void play(int players, int lastMarble) {
	//circle[0] = 0;
	circle2.clear();
	circle2.push_back(2); //len3 //player2
	circle2.push_back(1); //len3 //player2
	circle2.push_back(3); //len3 //player2
	circle2.push_back(0); //len3 //player2
	circle2.push_back(4); //len3 //player2

	unsigned long long score[450] = {0};
	int origI = 4;
	for (int i = 5; i < cSIZE; i++) {
		if (origI + 1000 > cSIZE) {printf("ERROR"); exit(0);}
		origI++;
		if (origI > lastMarble) {break;}
		int pl = origI % players;

		if ((origI % 23) != 0) {
			rotateClock(1);
			circle2.push_back(origI);
		} else {
	                score[pl] += origI;
			rotate(7);
			score[pl] += circle2.back();
			circle2.pop_back();
			rotateClock(1);
			i-=2;
		}

#ifdef _DEBUG_
		printf("[%d]   0  ", pl);
		for (int j = 0; j < i; j++) {
			if (j == curpos) {
				printf("(%d)", circle[j]);
			} else {
				printf(" %d ", circle[j]);
			}
		}
		if (twothree == 1) {getchar();}
		printf("\n");
		if (lastMarble > 7000000 && (origI % (lastMarble/100)) == 0) {
			unsigned long long max = 0;
			for (int s = 0; s < players; s++) {
				if (score[s] > max) {max = score[s];}
			}
			printf("INTERIM SCORE (%d): %llu (c.size: %d)\n", (origI/(lastMarble/100)), max, origI);
		}
#endif
	} 
	unsigned long long max = 0;
	for (int s = 0; s < players; s++) {
		if (score[s] > max) {max = score[s];}
	}
	printf("MAX SCORE %llu\n", max);
}
