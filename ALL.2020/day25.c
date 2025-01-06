#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include <unistd.h>

#define getchar()
int leny = 0;

int LINE = 1000;


int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        FILE *a = fopen(argv[1], "r"); printf("2020 Day25 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
	int cardPubKey;
	int doorPubKey;
while (1) {
        fgets(line1, LINE-1, a);
        //printf("LINE: %s\n", line1);
        if (feof(a)) break;
	line1[strlen(line1) -1] = '\0';
	//lenx = strlen(line1);

	if (leny == 0) {
		cardPubKey = atoi(line1);
	} else {
		doorPubKey = atoi(line1);
	}
	leny++;
}
	int val = 1;

	int cardLoopSize = 0;
	do {
		val = val * 7;
		val = val % 20201227;
		cardLoopSize++;
		//printf("val is %d\n", val);
	} while (val != cardPubKey);

	printf("part1 over...\n");
	int doorLoopSize = 0;
	val = 1;
	do {
		val = val * 7;
		val = val % 20201227;
		doorLoopSize++;
		//printf("val is %d\n", val);
	} while (val != doorPubKey);
	printf("part2 over...\n");
	printf("cardLoopSize: %d\n", cardLoopSize);
	printf("doorLoopSize: %d\n", doorLoopSize);

	unsigned long long enc1 = 1;
	for (int i = 0; i < doorLoopSize; i++) {
		enc1 = enc1 * cardPubKey;
		enc1 = enc1 % 20201227;
	}
	
	printf("part3 over...\n");
	printf("enckey is %llu\n", enc1);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", enc1);

	unsigned long long enc2 = 1;
	for (int i = 0; i < cardLoopSize; i++) {
		enc2 = enc2 * doorPubKey;
		enc2 = enc2 % 20201227;
	}
	assert(enc2 == enc1);
}
