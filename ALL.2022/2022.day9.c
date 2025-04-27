#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
#define S 7000
char wherebeen[S][S] = {0};
void show();
FILE *a;
void movetail();
int headx = S/2;
int heady = S/2;
int tailx = S/2;
int taily = S/2;
#define getchar()
int main(int argc, char **argv)
{
	////printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	a = fopen(argv[1], "r"); printf("		2022 Day9.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
	char line1[1000];

	int leny = 0;
	wherebeen[taily][tailx]++;
	while (1) {
		fgets(line1, 999, a);
		printf("LINE: %s\n", line1);
		if (feof(a)) break;
		line1[strlen(line1)-1] = '\0';	

		char LRUD; int dist;
		sscanf(line1, "%c %d\n", &LRUD, &dist);		

		switch (LRUD) {
			case 'L':
				printf("left %d\n", dist);
				for (int i = 0; i < dist; i++) {
					headx--;
					movetail();
					//show();
				}
				break;
			case 'R':
				printf("right %d\n", dist);
				for (int i = 0; i < dist; i++) {
					headx++;
					movetail();
					//show();
				}
				break;
			case 'U':
				printf("up %d\n", dist);
				for (int i = 0; i < dist; i++) {
					heady--;
					movetail();
					//show();
				}
				break;
			case 'D':
				printf("down %d\n", dist);
				for (int i = 0; i < dist; i++) {
					heady++;
					movetail();
					//show();
				}
				break;
		}
		leny++;
	}

	fclose(a);
	for (int y = (S/2) -10; y < (S/2)+10; y++) {
		for (int x = (S/2)-10; x < (S/2)+10; x++) {
			printf("%d", wherebeen[y][x]);
		}
		printf("\n");
	}
	printf("\n");
	unsigned long long tot = 0;
	for (int y = 0; y < S; y++) {
		for (int x = 0; x < S; x++) {
			if (wherebeen[y][x] > 0) {
				tot++;
			}
		}
	}
	//	tot+= 1;
	printf("****tot %llu\n", tot);

	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", tot);

}
void show() {
	for (int y = (S/2) -15; y < (S/2)+15; y++) {
		for (int x = (S/2)-15; x < (S/2)+15; x++) {
			if (headx == x && heady == y) {
				printf("H");
			} else if (tailx == x && taily == y) {
				printf("T");
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
	printf("\n"); getchar();
}


void movetail() {
	if (taily == heady && tailx == headx) {
		wherebeen[taily][tailx]++;
	} else if (taily == heady) { //left right same line
		if (abs(tailx - headx) > 1) {
			tailx > headx? tailx--: tailx++;
			wherebeen[taily][tailx]++;
		}
	} else if (tailx == headx) {
		if (abs(heady - taily) > 1) {
			taily > heady? taily--: taily++;
			wherebeen[taily][tailx]++;
		}
	} else { // off line
		if (abs(headx - tailx) + abs(heady-taily) > 2) {
			tailx > headx? tailx--: tailx++;
			taily > heady? taily--: taily++;
			wherebeen[taily][tailx]++;
		}
	}
}
