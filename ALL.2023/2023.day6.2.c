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

int main(int argc, char **argv)
{

	/*
Time:        53     91     67     68
Distance:   250   1330   1081   1025
*/

	a = fopen(argv[1], "r"); printf("		2023 Day 6.2\n"); fflush(stdout);
	fflush(stdout); int fd = dup(1); //close(1);
	char line1[LINE];

	leny = 0;
	char time[100] = "";
	char dist[100] = "";
	while (1) {
		fgets(line1, LINE-1, a);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';
		//printf("LINE: %s\n", line1);
		if (line1[0] == 'T') {
			char *fir = strtok(line1, " ");
			fir = strtok(NULL, " ");
			do {
				//timedist[pos++].time = atoi(fir);
				strcat(time, fir);
			} while ((fir = strtok(NULL, " ")) != NULL);
		} else if (line1[0] == 'D') {
			char *fir = strtok(line1, " ");
			fir = strtok(NULL, " ");
			do {
				//timedist[pos++].dist = atoi(fir);
				strcat(dist, fir);
			} while ((fir = strtok(NULL, " ")) != NULL);
		}

		leny++;
	}
	fclose(a);

	char *bla;
	unsigned long long t1 = strtoull(time, &bla, 10);
	unsigned long long d1 = strtoull(dist, &bla, 10);
	//printf("%llu %llu\n", t1, d1);
	unsigned long long numdistances = 0;
	for (unsigned long long i = 0; i < t1; i++) {
		unsigned long long speed = i;
		unsigned long long distance = speed * (t1 - speed);
		if (distance > d1) {
			numdistances++;
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", numdistances);
}

