#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <algorithm>

using namespace std;

FILE *a;
int aR[1200];
int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2020 Day9\n"); fflush(stdout);
        char line1[1000];
	
int leny = 0;
while (1) {
        fgets(line1, 500, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	int ret;
	int num; 
	ret = sscanf(line1, "%d", &num);
	if (ret == 1) {
		aR[leny] = num;
	}
	leny++;
}
fclose(a);

	int NUMS = 25;
	int iPos = 0;
	for (int i = NUMS; i < leny; i++) {
			int found = 0;
			for (int z = i - NUMS; z < i - 1; z++) {
				for (int q = i - NUMS + 1; q < i; q++) {
					if (aR[i] == (aR[z] + aR[q])) {
						found = 1; goto end;
					}
				}
			}
end:
			if (found == 0) {
				iPos = i;
				printf("****i:%d aR[i] is %d\n", i, aR[i]); goto next;
			}
	}

next:

	for (int i = 0; i < iPos; i++) {
		int mynum = 2;	
		int mysum;
restart:
		mynum++; mysum = 0;
		if (mynum + i >= iPos) {continue;}
		int j;
		for (j = 0; j < mynum; j++) {
			mysum += aR[i+j];	
		}
		if (mysum == aR[iPos]) {
			int mysort[1000];
			for (int k = 0; k < j; k++) {
				mysort[k] = aR[i+k];
			}
			sort(mysort, mysort+j);
			printf("found it.. pos %d nums(%d) SUM: %d\n", i, j, mysort[0]+mysort[j-1]); exit(0);
		} else {
			goto restart;
		}
	}
}
