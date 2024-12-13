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
#include <deque>
#include <string>


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
deque <unsigned long long> q1;
deque <string> q2;
void calcq1();

int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 7 Part 1\n"); fflush(stdout);
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
		printf("new...\n");
		for (int end = 0; end <= len; end++) {
			ve.clear();
			for (int k = 0; k < end; k++) {
				ve.push_back(0);
			}
			vector <int> tmpv;
			tmpv = ve;
			for (int end2 = end; end2 <= len; end2++) {
				ve = tmpv;
				for (int kk = end; kk < end2; kk++) {
					ve.push_back(1);
				}
				for (int kk2 = end2; kk2 < len; kk2++) {
					ve.push_back(2);
				}
			
				do {
					//q1.clear();	q1.push_back(sum[i].vars[0]);
					for (int kkk = 0; kkk < len; kkk++) {
						if (ve[kkk] == 0) {
							an += sum[i].vars[kkk+1];
							//q1.push_back(0);
							//q1.push_back(sum[i].vars[kkk+1]);
						} else if (ve[kkk] == 1) {
							an *= sum[i].vars[kkk+1];
							//q1.push_back(1);
							//q1.push_back(sum[i].vars[kkk+1]);
						} else if (ve[kkk] == 2) {
							an
							calcq1();
							q1.clear();
							q1.push_back(sum[i].vars[kkk+1]);
						}
					}
					calcq1();	
					int sz2 = q2.size();
					string ans3 = q2.front();
					q2.pop_front();
					
					for (int z1 = 1; z1 < sz2; z1++) {
						ans3 += q2.front();
						q2.pop_front();
					}
					char *blah;
					unsigned long long an;
					an = strtoull(ans3.c_str(), &blah, 10);
					if (an == prod) {
						printf("got an answer: %llu\n", an);
						tot += an;
						num1++;
						goto nextNum;
					}

				} while (next_permutation(ve.begin(), ve.end()));
			}
		}
nextNum:
		continue;
	}
	printf("num1: %d of leny: %d\n", num1, leny);
	printf("**ans %llu\n", tot);
			
}


void calcq1() {
	int sz = q1.size();
	
	unsigned long long ans2 = q1.front();
	q1.pop_front();
	for (int zzz = 0; zzz < sz/2; zzz++) {
		if (q1.front() == 0) {
			q1.pop_front();
			ans2 += q1.front();
			q1.pop_front();
		} else if (q1.front() == 1) {
			q1.pop_front();
			ans2 *= q1.front();
			q1.pop_front();
		} else {
			printf("err\n"); exit(0);
		}
	}
	assert((int)q1.size() == 0);
	
	char ans2s[50];
	sprintf(ans2s, "%llu", ans2);
	printf("ans2: %llu\n", ans2);
	q2.push_back(ans2s);
}

/*printf("len is %d end is %d end2 is %d\n", len, end, end2);
for (int zz = 0; zz < len; zz++) {
printf("%d ", ve[zz]);
} printf("\n"); getchar();
					*/
