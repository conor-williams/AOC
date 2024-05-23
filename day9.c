#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#undef _DEBUG_
#define SIZE 40000
char line1[SIZE];
unsigned long tot = 0;
#define cSIZE 8000000
int circle[cSIZE] = {0};
void play(int players, int lastMarble);
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
	circle[0] = 2;
	circle[1] = 1; //len2 //player2
	circle[2] = 3; //len3 //player2

	unsigned long long score[450] = {0};
	int curpos = 2;
	int origI = 3;
	for (int i = 4; i < cSIZE; i++) {
		if (origI + 1000 > cSIZE) {printf("ERROR"); exit(0);}
		origI++;
		if (origI > lastMarble) {break;}
		int pl = origI % players;
		if ((origI % 23) != 0) {
			curpos = (curpos+2) % (i);
			//printf("curpos %d\n", curpos);
			int tmpcircle[cSIZE];
			for (int z = 0; z < curpos; z++) {
				tmpcircle[z] = circle[z];
			}
			tmpcircle[curpos] = origI;
			for (int q = curpos+1; q < i+1; q++) {
				tmpcircle[q] = circle[q-1];
			}
			for (int r = 0; r < i; r++) {
				circle[r] = tmpcircle[r];
			}
		} else {
			score[pl] += origI;
			curpos = ((curpos+i)-7) % (i);
			score[pl] += circle[curpos];
			//printf("player %d points %d aiming for %d\n", pl, score[pl], points); break;

			int tmpcircle[cSIZE];
			for (int z = 0; z < curpos-1; z++) {
				tmpcircle[z] = circle[z];
			}
			for (int q = curpos; q < i+1; q++) {
				tmpcircle[q] = circle[q+1];
			}
			for (int r = 0; r < i-1; r++) {
				circle[r] = tmpcircle[r];
			}
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
#endif
		if (origI % 10000 == 0) {
			unsigned long long max = 0;
			for (int s = 0; s < players; s++) {
				if (score[s] > max) {max = score[s];}
			}
			printf("INTERIM SCORE %llu\n", max);
		}
	} 
	unsigned long long max = 0;
	for (int s = 0; s < players; s++) {
		if (score[s] > max) {max = score[s];}
	}
	printf("MAX SCORE %llu\n", max);
}
