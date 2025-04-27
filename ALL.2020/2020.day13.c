#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int lenx = 0;
int leny = 0;
int LINE = 1000;
int main(int argc, char **argv)
{
        ///printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("		2020 Day13 Part1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

	int var_ts;
	int busI[100] = {0};
	int busPos = 0;
while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	//line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);
	if (leny == 0) {
		sscanf(line1, "%d", &var_ts);
	} else if (leny == 1) {
		char *buses = strtok(line1, ",\n");
		busPos = 0;
		do {
			if (strcmp(buses, "x") != 0) {
				busI[busPos++] = atoi(buses);
			}
		} while ((buses = strtok(NULL, ",\n"))!=NULL);
	}
	leny++;
}
	
	printf("busPos is %d\n", busPos);
	for (int i = 0; i < busPos; i++) {
		printf("%d: %d\n", i, busI[i]);
	}
	
	int minTime = var_ts;
	int minBus;
	for (int j = 0; j < busPos; j++) {
		if (var_ts%busI[j] == 0) {
			printf("we have a winner - %d\n", busI[j]);
		} else {
			printf("%d mod %d = %d -- diff [ %d ]\n", var_ts, busI[j], var_ts%busI[j],
				busI[j] - (var_ts%busI[j]));
		}
		
		if ((busI[j] - (var_ts%busI[j])) < minTime) {
			minTime = busI[j] - (var_ts%busI[j]);
			minBus = busI[j];
			
		}
	}

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %d\n", minTime * minBus);
}
