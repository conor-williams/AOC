#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx = 0;
int leny = 0;
int main(int argc, char **argv)
{
        ////printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("		2020 Day12 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[1000];

	int curDir = 1;
	int NS = 0, EW = 0;
	int var_d;
while (1) {
        fgets(line1, 50, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);
	char command;
	command = line1[0];
	line1[0] = ' ';
	int dist;
	sscanf(line1, " %d", &dist);
	if (command == 'R') {
		switch (dist) {
			case 0: var_d = 0;
				break;
			case 90:
				var_d = 1;
				break;
			case 180:
				var_d = 2;
				break;
			case 270:
				var_d = 3;
				break;
			default:
				printf("Unk\n"); exit(0);
	
		}
	} else if (command == 'L') {
		switch (dist) {
			case 0:
				var_d = 0;
				break;
			case 90:
				var_d = 3;
				break;
			case 180:
				var_d = 2;
				break;
			case 270:
				var_d = 1;
				break;
			default:
				printf("Unk\n"); exit(0);
		}
	}


	switch (command) {
		case 'F':
			switch (curDir) {
				case 0:
					NS += dist;
					break;
				case 1:
					EW += dist;
					break;
				case 2:
					NS -= dist;
					break;
				case 3:
					EW -= dist;
					break;
			}
			break;
		case 'L':
		case 'R':
			curDir = ((curDir + var_d) + 4) % 4;
			break;
		case 'N':
			NS += dist;
			break;
		case 'S':
			NS -= dist;
			break;
		case 'E':
			EW += dist;
			break;
		case 'W':
			EW -= dist;
			break;
		default:
			printf("UNK\n"); exit(0);
	}
	leny++;
}

	printf("NS: %d\n", NS);
	printf("EW: %d\n", EW);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", abs(NS) + abs(EW));
}
