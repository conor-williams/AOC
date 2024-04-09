#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

int tot = 0;
int weights[200];
#define getchar()
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("Day24.1\n"); fflush(stdout);
	char line1[1000];
	int leny = 0;
	while (1) {

		fgets(line1, 900, a); if (feof(a)) {break;}
		line1[strlen(line1) -1] = '\0';
		// printf("line1 %s", line1);

		weights[leny] = atoi(line1);
		leny++;

	} //while
	fclose(a);

	int weTot = 0;
	sort(weights, weights+leny);
	for (int i = 0; i < leny; i++) {
		weTot += weights[i];
		printf("weights[i] :: %d\n", weights[i]);
	}
	weTot = weTot/3;
	printf("weTot is %d\n", weTot); getchar();

	struct qua {
		int num1;
		int QE;
	};
	struct qua mine[2000];
	int minePos = 0;
	unsigned long long int count1 = 0;
	do {
		int sum1 = 0; int pos = 0; int num1 = 0;
		int QE = 1;
		while (sum1 < weTot) {
			sum1 += weights[pos];
			QE *= weights[pos];
			num1++;
			pos++;
		}
		if (sum1 != weTot) {continue;}
		int sum2 = 0; int num2 = 0;
		while (sum2 < weTot) {
			sum2 += weights[pos];
			num2++;
			pos++;
		}
		if (sum2 != weTot) {continue;}
		count1++; if ((count1 % 10000) == 0) {count1 = 0; printf("mark...\n");} 
/*
		int sum3 = 0; int num3 = 0;
		while (sum3 < weTot) {
			sum3 += weights[pos];
			num3++;
			pos++;
		}
*/
	//	if (sum1 == sum2 && sum2 == sum3) {
			mine[minePos].num1 = num1;
			mine[minePos].QE = QE;
			minePos++;
			//printf("%d is num1 %d is QE\n", num1, QE);
	//	}


	} while (next_permutation(weights, weights+leny));

	int min = 10000;
	for (int i = 0; i < minePos; i++) {
		if (mine[i].num1 < min) {min = mine[i].num1;}
	}
	printf("min is %d\n", min);
	int minQE = 100000;
	for (int i = 0; i < minePos; i++) {
		if  (mine[i].num1 == min) {
			if (mine[i].QE < minQE) {minQE = mine[i].QE;}
		}
	}
	printf("***minQE: %d\n", minQE);
}


