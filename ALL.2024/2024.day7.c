#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <algorithm>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
//#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

struct sum_s {
	unsigned long long ans;
	vector <unsigned long long>vars;
};
struct sum_s sum[1000];

int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 7 Part 1\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];

int leny = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);

	char *fir = strtok(line1, ": \0");
	int first = 1;
	char *pEnd;
	do {
		if (first == 1) {
			first = 0;
			sum[leny].ans = strtoull(fir, &pEnd, 10);
		} else {
			sum[leny].vars.push_back(strtoull(fir, &pEnd, 10));
		}
	} while ((fir = strtok(NULL, ": \0")) != NULL);
	leny++;
}
fclose(a);

	unsigned long long tot = 0;
	int num1 = 0;
	for (int i = 0; i < leny; i++) {
		int len = sum[i].vars.size() -1;
		unsigned long long prod = sum[i].ans;
		
		vector <int> ve;
		for (int end = 0; end <= len; end++) {
			
			ve.clear();
			for (int k = 0; k < end; k++) {
				ve.push_back(0);
			}
			for (int kk = end; kk < len; kk++) {
				ve.push_back(1);
			}
		
			/*printf("len is %d end is %d\n", len, end);
			for (int zz = 0; zz < len; zz++) {
				printf("%d ", ve[zz]);
			} printf("\n"); getchar();
			*/
			do {
				unsigned long long an = sum[i].vars[0];
				for (int kkk = 0; kkk < len; kkk++) {
					if (ve[kkk] == 0) {
						an += sum[i].vars[kkk+1];
					} else if (ve[kkk] == 1) {
						an *= sum[i].vars[kkk+1];
					}	
				}
				if (an == prod) {
					printf("got an answer: %llu\n", an);
					tot += an;
					num1++;
					goto nextNum;
				}
			} while (next_permutation(ve.begin(), ve.end()));
		}
nextNum:
		continue;
	}
	printf("num1: %d of leny: %d\n", num1, leny);

	fflush(stdout); dup2(fd, 1);
	printf("**ans %llu\n", tot);
			
}
