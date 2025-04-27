#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
int lenx = 0;
int leny = 0;

struct  way_s {
	int N;
	int E;
	int S;
	int W;
};
struct way_s way;

struct pos_s {
	int N;
	int E;
	int S;
	int W;
};
struct pos_s pos;

int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

	FILE *a = fopen(argv[1], "r"); printf("		2020 Day12 Part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	way.N = +1; way.E = +10; way.S = 0; way.W = 0;
	pos.N = 0;  pos.E = 0;   pos.S = 0; pos.W = 0;

	while (1) {
		fgets(line1, 50, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1) -1] = '\0';
		//lenx = strlen(line1);
		char command = line1[0];
		line1[0] = ' ';
		int dist; sscanf(line1, " %d", &dist);
		printf("command is %c dist is %d\n", command, dist);
		switch(command) {
			case 'R': 
				//clockwise
				assert(dist == 90 || dist == 180 || dist == 270);
				assert(dist/90 >= 1 && dist/90 <= 3);
				for (int i = 0; i < dist/90; i++) {
					struct way_s waytmp = way;
					way.N = waytmp.W;
					way.E = waytmp.N;
					way.S = waytmp.E;
					way.W = waytmp.S;
				}
				break;
			case 'L': 
				//anticlock
				assert(dist == 90 || dist == 180 || dist == 270);
				assert(dist/90 >= 1 && dist/90 <= 3);
				for (int i = 0; i < dist/90; i++) {
					struct way_s waytmp = way;
					way.N = waytmp.E;
					way.E = waytmp.S;
					way.S = waytmp.W;
					way.W = waytmp.N;
				}
				break;
			case 'N':
				way.N += dist;
				break;
			case 'E':
				way.E += dist;
				break;
			case 'S': 
				way.S += dist;
				break;
			case 'W':
				way.W += dist;
				break;
			case 'F':
				pos.N += dist*way.N;
				pos.E += dist*way.E;
				pos.S += dist*way.S;
				pos.W += dist*way.W;
				break;
			default:
				printf("ERROR command %c\n", command);
				printf("UNK\n"); exit(0);
		}

		pos.N = pos.N-pos.S; pos.S = 0;
		if (pos.N < 0) {pos.S = -pos.N; pos.N = 0;}
		pos.E = pos.E-pos.W; pos.W = 0;
		if (pos.E < 0) {pos.W = -pos.E; pos.E = 0;}

		way.N = way.N-way.S; way.S = 0;
		if (way.N < 0) {way.S = -way.N; way.N = 0;}
		way.E = way.E-way.W; way.W = 0;
		if (way.E < 0) {way.W = -way.E; way.E = 0;}
		leny++;
	}

	printf("leny is %d\n", leny);
	fflush(stdout); dup2(fd, 1);

	printf("**ans: %d\n", abs(pos.N-pos.S) + abs(pos.E-pos.W));
}
