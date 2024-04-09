#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int isAlready(int num);
int arr[10000] = {0};
int endarr = 0;
void main(int argc, char **argv)
{
long numdistances1 = 0;
	for (long i = 0; i < 53916768; i++) {
		long speed = i;
		long distance = speed * (53916768 - speed);
if (distance > 250133010811025) {
		numdistances1++;
}
	}
		printf("numdistances = %d\n", numdistances1);

int numdistances2 = 0;
	for (int i = 0; i < 91; i++) {
		int speed = i;
		int distance = speed * (91 - speed);
if (distance > 1330) {
		numdistances2++;
}
	}
		printf("numdistances = %d\n", numdistances2);

int numdistances3 = 0;
	for (int i = 0; i < 67; i++) {
		int speed = i;
		int distance = speed * (67 - speed);
if (distance > 1081) {
		numdistances3++;
}
	}
		printf("numdistances = %d\n", numdistances3);

int numdistances4 = 0;
	for (int i = 0; i < 68; i++) {
		int speed = i;
		int distance = speed * (68 - speed);
if (distance > 1025) {
		numdistances4++;
}
	}
		printf("numdistances = %d\n", numdistances4);
printf("Tot %ld\n", numdistances1);
}

