#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
/*
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <algorithm>
//#include <unsorted_set>

using namespace std;
*/


FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }
int lenx;
int leny;

int main(int argc, char **argv)
{
        clock_t start, end; double cpu_time_used; 
	start = clock();
	//DO
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("        time: %f seconds\n", cpu_time_used);

        //signal(SIGTSTP, &sigfunc);
        signal(SIGQUIT, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day ***XYZXYZ** Part *XYZ**\n"); fflush(stdout);
        char line1[LINE];

	leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	leny++;
}
fclose(a);

}
