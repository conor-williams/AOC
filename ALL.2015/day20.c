#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <unistd.h>

#define getchar()
int tot = 0;
#define INP 29000000
int presents[INP+100] = {0};
int NUMHOUSES = INP;
int sumit(int housei);
int up;
int main(int argc, char **argv)
{
	printf("%d", argc);
	printf("2015 Day20.1\n"); fflush(stdout);
	printf("Using Input %d\n", NUMHOUSES);

	fflush(stdout); int fd = dup(1); close(1);
	int housei = 0;
	for (up = 0; ; up++) {
		int su = (up*(up+1)/2) *10;
		if (su > NUMHOUSES) {up--; break;}
	}
	housei = up;
	while (sumit(housei) < INP) {
		housei++;
	}

	dup2(fd, 1);
	printf("**ans: %d\n", housei);
	exit(0);

}

int sumit(int housei) {
	int interimtot = 0;
	int d = (int)sqrt((double)housei)+1; 
	for (int fact = 1; fact <= d; fact++) {
		if (housei % fact == 0) {
			interimtot += fact;
			interimtot += housei/fact;
		}
	}
	interimtot *= 10;
	return interimtot;
}
