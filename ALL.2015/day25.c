#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//To continue, please consult the code grid in the manual.  Enter the code at row 2978, column 3083.

unsigned long long int rc[8000][3200] = {0};
int tot = 0;

int main(int argc, char **argv)
{
        printf("%d", argc); printf("%s", argv[1]); fflush(stdout);

        FILE * a = fopen(argv[1], "r"); printf("Day25.1\n"); fflush(stdout);
        char line1[1000];
        int leny = 0;
        while (1) {
                fgets(line1, 1000, a); if (feof(a)) {break;}
                line1[strlen(line1) -1] = '\0';
//              printf("line1 %s", line1);
		sscanf(line1, "%llu %llu %llu %llu %llu %llu", &rc[leny][0], &rc[leny][1], &rc[leny][2], 
			&rc[leny][3], &rc[leny][4], &rc[leny][5]);
		leny++;
        } //while
        fclose(a);

/*
	for (int i = 0; i < 1; i++) {
		unsigned long long next = ((rc[1][0] * 252533) % 33554393);
		printf("next\n%llu\n%llu\n", next, rc[0][1]);
	}
	
	row 6 6 has 6
	last in diag 4 is 10 which is 1+2+3+4
*/
	//area of equi gives 25 which is of the 4*4
	int lastNum = 0;
	int mynum = 0;
	for (int d = 1; d < 8000; d++) {
		int fromNum = lastNum+1; //or lastNum -d 
		lastNum += d;
		//printf("from [%d] to [%d] in diag [%d] (*%d)\n", fromNum, lastNum, d, lastNum-d);
		//printf("to [%d] from [%d] in diag [%d] (*%d)\n", lastNum, fromNum, d, lastNum-d);
		for (int y = 0; y < d; y++) {
			//for (int x = d-1; x >= 0; x--) {
			int x = d-y-1;
			//printf("%d,%d ", y, x);
			if (y == 2977 && x == 3082) {
//			if (y == 1 && x == 4) { //gives 14
				printf("from [%d] to [%d] in diag [%d] (*%d)\n", fromNum, lastNum, d, lastNum-d);
				/*y==0*/
				printf("to [%d] from [%d] in diag [%d] (*%d)\n", lastNum, fromNum, d, lastNum-d);
				//printf("is it %d\n", lastNum - 2978);
				printf("is it %d\n", lastNum - 1);
				mynum = lastNum - 2977;
				//mynum = lastNum - 2978;
			}
				
			//printf("\n");
		}
	}
	unsigned long long next = 20151125;
	for (int i = 1; i < mynum; i++) {
		next = ((next * 252533) % 33554393);
	}
	printf("***next: %llu \n", next);
	
			
        printf("***tot: %d\n", tot);
}

