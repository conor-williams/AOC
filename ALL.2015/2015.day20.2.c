#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define INP 29000000
int NUMHOUSES = INP;
int main(int argc, char **argv)
{
        //printf("%d", argc);

        printf("		2015 Day20.2\n"); fflush(stdout);
	//printf("Using Input %d\n", NUMHOUSES);

	fflush(stdout); int fd = dup(1); close(1);
	int up;
	for (up = 0; ; up++) {
		int su = (up*(up+1)/2) * 10;
		if (su > NUMHOUSES) {up--; break;}
	}
	printf("up is %d\n", up);
	for (int housei = up; ; housei++ /*=1*2*3*5*7*/) {
		int interimtot = 0;
		int e = (int)sqrt((double)housei) + 1;
		for (int fact = 1; fact <= e; fact++) {
			if ((housei % fact) == 0) {
				if ((fact*50) >= housei) {
					interimtot += fact;
				}
				int val;
				if ((val = housei/fact) *50 >= housei) {
					interimtot += val;
				}
			 }
		}

		interimtot *= 11;

		if (interimtot >= NUMHOUSES) {
			fflush(stdout); dup2(fd, 1);
                        printf("**ans: %d\n", housei);
                        exit(0);
		}
        }
	printf("after...\n");

	/*
        for (int housei = 0; housei < NUMHOUSES; housei += 1*3*5*7) {
		int interimtot = 0;
		for (int fact = 1; fact <= housei; fact++) {
			int thistot = 0;
			if (housei % fact == 0) {
				interimtot += fact * 10;
			 }
		}
		if (interimtot >= NUMHOUSES) {
			for (int fact = 1; fact <= housei; fact++) {
				int thistot = 0;
				if (housei % fact == 0) {
					printf("fact %d\n", fact);
				}
			}
			printf("interimtot is %d\n", interimtot);
                        printf("**ans: %d\n", housei);
                        exit(0);
		}
        }
	*/
        for (int housei = 1; housei < 10; housei++) {
                //printf("house %d got %d presents\n", housei, presents[housei]);
        }

        printf("***tot: %d\n", tot);
}

