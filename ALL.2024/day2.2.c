#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <vector>
#include <signal.h>

#include <unistd.h>

#define getchar()
#define assert(asdf)
using namespace std;

FILE *a;
#define LINE 1000
#define getchar()
void sigfunc(int a) { printf("[[ %s ]]\n", "signal hand..\n"); }

vector <int> vec;
vector <int> vecOrig;
int main(int argc, char **argv)
{
        signal(SIGTSTP, &sigfunc);
        printf("%d", argc); printf("%s\n", argv[1]); fflush(stdout);

        a = fopen(argv[1], "r"); printf("2024 Day 2 part2\n"); fflush(stdout);

	fflush(stdout); int fd = dup(1); close(1);
        char line1[LINE];
        char line2[LINE];

int leny = 0;
	unsigned long long num = 0;
while (1) {
        fgets(line1, LINE-1, a);
        if (feof(a)) break;
        line1[strlen(line1)-1] = '\0';
        printf("LINE: %s\n", line1);
	strcpy(line2, line1);
	char *first = strtok(line1, " \0");
	char *secon = strtok(NULL, " \0");
	int pos = 0, posPrev;
	int bad = 0;
	int init = 1;
	do {
		int fir = atoi(first);
		int sec = atoi(secon);
		//int val = atoi(first) - atoi(secon);
		int val = fir - sec;
		printf("%s -- %s val is %d\n", first, secon, val);
		//sign
		if (init == 1) {
			if (val > 0) {
				pos = 1;
			} else if (val < 0) {
				pos = 0;
			}
		} else if (init == 0) {
			posPrev = pos;
			if (val > 0) {
				pos = 1;
			} else if (val < 0) {
				pos = 0;
			}

			if (posPrev != pos) {
				bad = 1;
				break;
			}
		}
		if (abs(val) >= 1 && abs(val) <= 3) {
			//ok
		} else {
			bad = 1; break;
		}
		first = secon;
		init = 0;
	} while ((secon = strtok(NULL, " \0")) != NULL);
	if (bad == 0) {
		num++;
	} else {
		char *f1 = strtok(line2, " \0");		
		char *f2 = strtok(NULL, " \0");
		int f1i, f2i;
		vec.clear();
		do {
			f1i = atoi(f1);
			f2i = atoi(f2);
			vec.push_back(f1i);

			f1 = f2;
			f1i = atoi(f1);
		} while ((f2 = strtok(NULL, " \0")) != NULL);
		vec.push_back(f2i);
		for (auto it = vec.begin(); it != vec.end(); it++) {printf(" %d ", *it); }
		printf("\n"); getchar();


		int len = vec.size();
		vecOrig = vec;
		for (int i = 0; i < len; i++) {
			vec = vecOrig;
			vec.erase(vec.begin()+i);
			int bad2 = 0;

			printf("leaving out pos %d\n", i);
			int init = 1;
			int pos = 0, posPrev;
			for (int j = 0; j < len-2; j++) {
				int fi = vec.at(j);
				int se = vec.at(j+1);

				printf("comparing %d V %d\n", fi, se);
				{
					int val = fi - se;
					if (init == 1) {
						if (val > 0) {
							pos = 1;
						} else if (val < 0) {
							pos = 0;
						}
					} else if (init == 0) {
						posPrev = pos;
						if (val > 0) {
							pos = 1;
						} else if (val < 0) {
							pos = 0;
						}

						if (posPrev != pos) {
							bad2 = 1; break;
						}
					}
					if (abs(val) >= 1 && abs(val) <= 3) {
						//ok
					} else {
						bad2 = 1; break;
					}
					//fi = se;
					init = 0;
				}
			}
			if (bad2 == 0) {num++; break;}
		}
			
	}
	leny++;
}

	fflush(stdout); dup2(fd, 1);
	printf("**ans %lld\n", num);
fclose(a);

}
