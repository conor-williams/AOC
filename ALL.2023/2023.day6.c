#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
FILE *a;
#define LINE 1000
int lenx;
int leny;
struct timedist_s {
	int time;
	int dist;
};
struct timedist_s timedist[10];
int main(int argc, char **argv)
{

/*
Time:        53     91     67     68
Distance:   250   1330   1081   1025
*/

	a = fopen(argv[1], "r"); printf("		2023 Day 6 Part 1\n"); fflush(stdout);
	fflush(stdout); int fd = dup(1); //close(1);
	char line1[LINE];

	leny = 0;
	int pos = 0;
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		if (line1[0] == 'T') {
			char *fir = strtok(line1, " ");
			fir = strtok(NULL, " ");
			pos = 0;
			do {
				timedist[pos++].time = atoi(fir);
			} while ((fir = strtok(NULL, " ")) != NULL);
		} else if (line1[0] == 'D') {
			char *fir = strtok(line1, " ");
			fir = strtok(NULL, " ");
			pos = 0;
			do {
				timedist[pos++].dist = atoi(fir);
			} while ((fir = strtok(NULL, " ")) != NULL);
		}

		leny++;
	}
	fclose(a);
	for (int kkk = 0; kkk < pos; kkk++) {
		//printf("%d %d\n", timedist[kkk].time, timedist[kkk].dist);
	}

	unsigned long long tot = 1;
	for (int kkk = 0; kkk < pos; kkk++) {
		long numdistances = 0;
		for (long i = 0; i < timedist[kkk].time; i++) {
			long speed = i;
			long distance = speed * (timedist[kkk].time - speed);
			if (distance > timedist[kkk].dist) {
				numdistances++;
			}
		}
		tot *= numdistances;
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", tot);
}

