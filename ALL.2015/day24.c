#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>
#include <string>
#include <unistd.h>

#include <unistd.h>

#define getchar()
using namespace std;

unsigned long long tot = 0;
int weights[200];
#define getchar()
int main(int argc, char **argv)
{
	printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

	FILE * a = fopen(argv[1], "r"); printf("Day24.1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
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

	unsigned long long weTot = 0;
	sort(weights, weights+leny);
	for (int i = 0; i < leny; i++) {
		weTot += weights[i];
		printf("weights[i] :: %d\n", weights[i]);
	}
	weTot = weTot/3;
	printf("weTot is %llu\n", weTot); getchar();

	struct qua {
		unsigned long long num1;
		unsigned long long QE;
	};
	struct qua mine[5000];
	int minePos = 0;
	unsigned long long mymin = 9999999999999999;
	tot = 0;
	for (int end = 0; end < leny; end++) {
		int arr[100] = {0};
		//		printf("end is %d leny is %d\n", end, leny);
		for (int i = 0; i < end; i++) {
			arr[i] = 1;
		}
		for (int i = end; i < leny;i++ ) {
			arr[i] = 0;
		}

		sort(arr, arr+leny);

		do {
			unsigned long long mysum = 0; unsigned long long QE = 1; unsigned long long num1 = 0;

			num1 = end;
			if (num1 > mymin) {break;}
			for (int j = 0; j < leny; j++) {
				if (arr[j] == 1) {
					mysum += weights[j];
					QE *= weights[j];
					//num1++;
				}
			}
			if (mysum == weTot && (mymin == 99999999999999999 || num1 <= mymin)) {
				//printf("%llu\n", weTot); printf("%llu\n", QE);
				int pos = 0; unsigned long long tmpW[100] = {0};
				for (int k = 0; k < leny; k++) {
					if (arr[k] == 0) {
						tmpW[pos] = weights[k]; pos++;
					}
				}
				for (int end1 = 0; end1 < pos; end1++) {
					int arr1[100] = {0};
					for (int l = 0; l < end1; l++) {
						arr1[l] = 1;
					}
					for (int m = end1; m < pos; m++) {
						arr1[m] = 0;
					}
					sort(arr1, arr1+pos);
					do {
						unsigned long long mysum1 = 0;
						unsigned long long QE2 = 1;
						for (int n = 0; n < pos; n++) {
							if (arr1[n] == 1) {
								mysum1 += tmpW[n];
								QE2 *= tmpW[n];
							}
						}
						if (mysum1 == weTot) {
							//printf("%llu\n", QE2);
							//{count = 1; printf("num1 %llu QE %llu tot %llu end1 is %d pos is %d\n", num1, QE, tot, end1, pos);}
							{
								int found = 0;
								for (int z = 0; z < minePos; z++) {
									if (mine[z].num1 == num1 && mine[z].QE == QE) {
										found = 1;
										break;
									}
								}
								if (num1 < mymin) {mymin = num1;}
								if (found == 0 || minePos == 0) {
									mine[minePos].num1 = num1;
									mine[minePos].QE = QE; minePos++;
									tot++;
									//printf("num1 %llu QE %llu tot %llu end2 is %d pos2 is %d\n", num1, QE, tot, end2, pos2);
									goto jump;
								}
							}
						}
					} while (next_permutation(arr1, arr1+pos));
				}
			}
jump:
			continue;
		}  while (next_permutation(arr, arr+leny));
	}
	printf("tot is %llu\n", tot); getchar();
	unsigned long long min = 1000;
	for (int i = 0; i < minePos; i++) {
		if (mine[i].num1 < min) {min = mine[i].num1;}
	}
	printf("min is %llu\n", min);
	//unsigned long long minQE = 22222889531;
	unsigned long long minQE = 99999999999999999;
	for (int i = 0; i < minePos; i++) {
		//if  (mine[i].num1 == min) {
		if (mine[i].QE < minQE) {minQE = mine[i].QE;}
		//}
	}

	printf("***minQE: %llu\n", minQE);
	fflush(stdout); dup2(fd, 1);
	printf("**ans: %llu\n", minQE);
}


/*
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

//		int sum3 = 0; int num3 = 0;
////		while (sum3 < weTot) {
//			sum3 += weights[pos];
//			num3++;
//			pos++;
//		}
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
*/
